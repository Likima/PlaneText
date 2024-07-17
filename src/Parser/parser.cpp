#include "parser.hpp"

// ---------------------------
// PARSER DEFINITIONS
// ---------------------------

std::shared_ptr<Error> Parser::advance()
{
    // used to parse each token individually.
    if (this->token_idx < this->tokenList.size() - 1)
    {
        this->token_idx++;
        this->current_token = tokenList[this->token_idx];
    }
    return nullptr;
}

std::shared_ptr<GenericNode> Parser::binop(std::shared_ptr<GenericNode> (Parser::*func)(), const std::vector<TokenType> &op_types)
{
    std::shared_ptr<GenericNode> left = (this->*func)();
    if (left->getErr() != nullptr)
        return left;

    while (std::find(op_types.begin(), op_types.end(), this->current_token.type) != op_types.end())
    {
        Token op = this->current_token;
        std::shared_ptr<Error> e = advance();
        if (e != nullptr)
        {
            left->setErr(e);
            return left;
        }
        std::shared_ptr<GenericNode> right = (this->*func)();
        if (right->getErr() != nullptr)
            return right;
        left = std::make_shared<BinOpNode>(op, left, right);
    }

    return left;
}

std::shared_ptr<GenericNode> Parser::factor()
{
    Token tok = this->current_token;
    std::shared_ptr<GenericNode> NumTok = std::make_shared<GenericNode>(tok);

    if (tok.type == TT_ADD || tok.type == TT_SUB) {
        *NumTok = UnaryOpNode(NumTok);
        advance();        
    }
    if (tok.type == TT_INT || tok.type == TT_FLOAT)
    {
        *NumTok = NumNode(NumTok);
        advance();
    }
    else if (tok.type == TT_LPAREN) {
        advance();
        NumTok = expr();
        // Should recursively run until a RPAREN is hit.
        if (current_token.type = TT_RPAREN) {
            advance();
        } else 
            NumTok->setErr(std::make_shared<Error>(SyntaxErr({tok.getPos().first, tok.getPos().second, "INVALID SYNTAX", "Expected a ')'."})));
    }
    else if (token_idx >= tokenList.size())
    {
        NumTok->setErr(std::make_shared<Error>(SyntaxErr({tok.getPos().first, tok.getPos().second, "UNEXPECTED EXPRESSION", "Invalid Synyax."})));
    }
    else {
        NumTok->setErr(std::make_shared<Error>(Error({tok.getPos().first, tok.getPos().second, "EXPECTED INT/FLOAT", "Binary operation expected a second argument."})));   
    }
    return NumTok;
    // TODO : Handle brackets
}

std::shared_ptr<GenericNode> Parser::term()
{
    return binop(&Parser::factor, {TT_MUL, TT_DIV});
}

std::shared_ptr<GenericNode> Parser::expr()
{
    return binop(&Parser::term, {TT_ADD, TT_SUB});
}

bool Parser::parse(std::vector<Token> tList)
{
    // TODO: refactor to make return bool on success/failure
    if (tList.empty())
        return false;

    tokenList = tList;
    token_idx = 0;

    this->current_token = tList[token_idx];
    std::shared_ptr<GenericNode> result = expr();
    if (result->getErr() != nullptr)
    {
        result->getErr()->printErr();
        return false;
    }
    result->printNode();
    ast = result;
    std::cout << std::endl;
    return true;
    // add stuff here later
}