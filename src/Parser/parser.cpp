#include "parser.hpp"

// ---------------------------
// WRAPPER DEFINITIONS
// ---------------------------

/*
    Wrapper &success(std::shared_ptr<GenericNode>);
    Wrapper &failure(Error e);
    std::shared_ptr<GenericNode> reg(std::variant<std::shared_ptr<GenericNode>, Wrapper>);
*/

Wrapper &Wrapper::success(std::shared_ptr<GenericNode> node)
{
    this->node = node;
    return *this;
}

Wrapper &Wrapper::failure(std::shared_ptr<Error> e)
{
    this->err = e;
    return *this;
}

std::shared_ptr<GenericNode> Wrapper::reg(std::variant<std::shared_ptr<GenericNode>, Wrapper> v)
{
    if (std::holds_alternative<Wrapper>(v))
    {
        Wrapper wrapper = std::get<Wrapper>(v);
        auto err = wrapper.getWrapperErr()->getErr();
        if (err != nullptr)
        {
            this->err = err;
        }
        return wrapper.node;
    }
    return std::get<std::shared_ptr<GenericNode>>(v);
}

// ---------------------------
// PARSER DEFINITIONS
// ---------------------------

void Parser::advance()
{
    // used to parse each token individually.
    if (this->token_idx < this->tokenList.size() - 2)
    {
        this->token_idx++;
        this->current_token = tokenList[this->token_idx];
    }
}

std::shared_ptr<GenericNode> Parser::binop(std::shared_ptr<GenericNode> (Parser::*func)(), const std::vector<TokenType> &op_types)
{
    std::shared_ptr<GenericNode> left = (this->*func)();

    while (std::find(op_types.begin(), op_types.end(), this->current_token.type) != op_types.end())
    {
        Token op = this->current_token;
        advance();
        std::shared_ptr<GenericNode> right = (this->*func)();
        left = std::make_shared<BinOpNode>(op, left, right);
    }

    return left;
}

std::shared_ptr<GenericNode> Parser::factor()
{
    Token tok = this->current_token;
    Token ERR;
    ERR.type = TT_NULL;
    ERR.text = "-1";

    if (tok.type == TT_INT || tok.type == TT_FLOAT)
    {
        advance();
        return std::make_shared<NumNode>(tok);
    }

    // TODO : Handle brackets
    return std::make_shared<GenericNode>(ERR);
}

std::shared_ptr<GenericNode> Parser::term()
{
    return binop(&Parser::factor, {TT_MUL, TT_DIV});
}

std::shared_ptr<GenericNode> Parser::expr()
{
    return binop(&Parser::term, {TT_ADD, TT_SUB});
}

void Parser::parse(std::vector<Token> tList)
{
    tokenList = tList;
    token_idx = 0;
    this->current_token = tList[token_idx];
    std::shared_ptr<GenericNode> result = expr();
    result->printNode();
    std::cout << std::endl;
    // add stuff here later
}