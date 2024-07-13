#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include "../Lexer/lexer.hpp"
#include "../globals.hpp"

#include <iostream>
#include <memory>

class GenericNode
{
private:
    Token GenericTok;

public:
    GenericNode(Token tok) : GenericTok(tok) {}
    virtual ~GenericNode() {}

    virtual Token getToken() const { return GenericTok; }
    virtual void printNode() const
    {
        std::cout << "here" << std::endl;
        GenericTok.printTokenWithoutEndl();
    }
};

// Classifies a Number Node
class NumNode : public GenericNode
{
private:
    Token NumNodeTok;

public:
    NumNode(Token tok) : GenericNode(tok), NumNodeTok(tok) {} // Constructor
    ~NumNode() {}                                             // Destructor

    Token getToken() const override { return NumNodeTok; }
    void printNode() const override { NumNodeTok.printTokenWithoutEndl(); }
};

// Classifies a BINARY OPERATION
class BinOpNode : public GenericNode
{
private:
    Token BinOpTok;
    std::shared_ptr<GenericNode> LNode;
    std::shared_ptr<GenericNode> RNode;

public:
    BinOpNode(Token tok, std::shared_ptr<GenericNode> left, std::shared_ptr<GenericNode> right)
        : GenericNode(tok), BinOpTok(tok), LNode(left), RNode(right) {}
    ~BinOpNode() {}

    Token getToken() const override { return BinOpTok; }
    void printNode() const override
    {
        std::cout << "( ";
        LNode->printNode();
        BinOpTok.printTokenWithoutEndl();
        RNode->printNode();
        std::cout << " )";
    }

    std::shared_ptr<GenericNode> getLeftNode() const { return LNode; }
    std::shared_ptr<GenericNode> getRightNode() const { return RNode; }
};

// PARSER CLASS

class Parser
{
private:
    std::vector<Token> tokenList;
    int token_idx = 0;
    Token current_token;

    void advance();

    std::shared_ptr<GenericNode> factor();
    std::shared_ptr<GenericNode> term();
    std::shared_ptr<GenericNode> expr();
    std::shared_ptr<GenericNode> binop(std::shared_ptr<GenericNode> (Parser::*func)(), const std::vector<TokenType> &op_types);

public:
    void processTokens(std::vector<Token> tokens) { tokenList = tokens; }
    void parse(std::vector<Token> tList);
};

#endif // PARSER_HPP
