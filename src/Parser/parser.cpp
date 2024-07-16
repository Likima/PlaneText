#include "parser.hpp"

// ---------------------------
// WRAPPER DEFINITIONS
// ---------------------------

// Wrapper &Wrapper::success(std::shared_ptr<GenericNode> node)
// {
//     this->node = node;
//     return *this;
// }

// Wrapper &Wrapper::failure(std::shared_ptr<Error> e)
// {
//     this->err = e;
//     return *this;
// }

// std::shared_ptr<GenericNode> Wrapper::reg(std::variant<std::shared_ptr<GenericNode>, Wrapper> v)
// {
//     if (std::holds_alternative<Wrapper>(v))
//     {
//         Wrapper wrapper = std::get<Wrapper>(v);
//         auto err = wrapper.getWrapperErr()->getErr();
//         if (err != nullptr)
//         {
//             this->err = err;
//         }
//         return wrapper.node;
//     }
//     return std::get<std::shared_ptr<GenericNode>>(v);
// }

// ---------------------------
// PARSER DEFINITIONS
// ---------------------------

std::shared_ptr<Error> Parser::advance()
{
    // used to parse each token individually.
    if (this->token_idx < this->tokenList.size() - 2)
    {
        this->token_idx++;
        this->current_token = tokenList[this->token_idx];
    }
    else
    {
        // Expected arg
        return std::make_shared<Error>(Error({current_token.getPos().first, current_token.getPos().second, "EXPECTED INT/FLOAT", "Binary operation expected a second argument."}));
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
        std::shared_ptr<Error> e = advance()->getErr();
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
    std::shared_ptr<NumNode> NumTok = std::make_shared<NumNode>(tok);

    if (tok.type == TT_INT || tok.type == TT_FLOAT)
    {
        std::shared_ptr<Error> e = advance()->getErr();
        if (e != nullptr)
            NumTok->setErr(e);
    }
    else
    {
        NumTok->setErr(std::make_shared<Error>(Error({tok.getPos().first, tok.getPos().second, "EXPECTED INT/FLOAT", "Binary operation expected a second argument."})));
        std::cout << "here!" << std::endl;
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
    std::cout << std::endl;
    return true;
    // add stuff here later
}