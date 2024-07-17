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
    virtual int getType() const { return GENERIC; }

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
    NumNode(std::shared_ptr<GenericNode>& gn) : GenericNode(gn->getToken()), NumNodeTok(gn->getToken()) {}; 

    Token getToken() const override { return NumNodeTok; }
    void printNode() const override { NumNodeTok.printTokenWithoutEndl(); }
    int getType() const override { return NUM; }
};

class UnaryOpNode : public GenericNode
{
private:
    Token UnOpTok;

public:
    UnaryOpNode(Token tok) : GenericNode(tok), UnOpTok(tok){}; // Constructor
    ~UnaryOpNode() {}
    UnaryOpNode(std::shared_ptr<GenericNode>& gn) : GenericNode(gn->getToken()), UnOpTok(gn->getToken()) {}; 

    Token getToken() const override { return UnOpTok; }
    void printNode() const override { UnOpTok.printTokenWithoutEndl(); }
    int getType() const override { return UNARY; }
};

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
    int getType() const override { return BIN; }

    std::shared_ptr<GenericNode> getLeftNode() const { return LNode; }
    std::shared_ptr<GenericNode> getRightNode() const { return RNode; }
};

// PARSER CLASS

class Parser
{
private:
    std::vector<Token> tokenList;
    std::shared_ptr<GenericNode> ast;
    int token_idx = 0;
    Token current_token;

    std::shared_ptr<Error> advance();

    std::shared_ptr<GenericNode> factor();
    std::shared_ptr<GenericNode> term();
    std::shared_ptr<GenericNode> expr();
    std::shared_ptr<GenericNode> binop(std::shared_ptr<GenericNode> (Parser::*func)(), const std::vector<TokenType> &op_types);

public:
    Parser(){};

    void processTokens(std::vector<Token> tokens) { tokenList = tokens; }
    bool parse(std::vector<Token> tList);
    std::shared_ptr<GenericNode> getAST() { return ast; }
};

#endif // PARSER_HPP
