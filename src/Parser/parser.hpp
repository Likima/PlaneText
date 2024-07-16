#ifndef PARSER_HPP
#define PARSER_HPP

#include "../Lexer/lexer.hpp"
#include "../globals.hpp"
#include "../errors.hpp"

#include <iostream>
#include <memory>
#include <variant>

/// Class for inheritence purposes
class GenericNode
{
private:
    Token GenericTok;
    std::shared_ptr<Error> err = nullptr;

public:
    GenericNode(Token tok) : GenericTok(tok) {}
    virtual ~GenericNode() {}

    virtual Token getToken() const { return GenericTok; }
    virtual void printNode() const { GenericTok.printTokenWithoutEndl(); }
    
    void setErr(std::shared_ptr<Error> e) { err = e; }
    std::shared_ptr<Error> getErr() { return err; }
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

class UnaryOpNode : public GenericNode
{
private:
    Token UnOpTok;

public:
    UnaryOpNode(Token tok) : GenericNode(tok), UnOpTok(tok){}; // Constructor
    ~UnaryOpNode() {}

    Token getToken() const override { return UnOpTok; }
    void printNode() const override { UnOpTok.printTokenWithoutEndl(); }
};

// class Wrapper : public GenericNode
// {
// private:
//     std::shared_ptr<GenericNode> node;
//     std::shared_ptr<Error> err;

// public:
//     Token getToken() const override { return node->getToken(); }
//     void printNode() const override { node->getToken().printTokenWithoutEndl(); }

//     Wrapper(){}; // Constructor
//     std::shared_ptr<GenericNode> getNode() { return node; }
//     std::shared_ptr<Error> getWrapperErr() { return err; }
//     Wrapper &success(std::shared_ptr<GenericNode>);
//     Wrapper &failure(std::shared_ptr<Error> e);
//     std::shared_ptr<GenericNode> reg(std::variant<std::shared_ptr<GenericNode>, Wrapper>);
// };

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
    Parser() {};
    void processTokens(std::vector<Token> tokens) { tokenList = tokens; }
    void parse(std::vector<Token> tList);
};

#endif // PARSER_HPP
