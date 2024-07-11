#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include "../Lexer/lexer.hpp"
#include "../globals.hpp"

class GenericNode {
private:
    Token GenericTok;
public:
    GenericNode(Token tok) : GenericTok(tok) {}
    virtual ~GenericNode() {}
    
    Token getToken() const { return GenericTok; }

    virtual void printTok() { GenericTok.printToken(); }
};

// Classifies a Number Node

class NumNode : public GenericNode {
private:
    Token NumNodeTok;
public:
    NumNode(Token tok) : GenericNode(tok), NumNodeTok(tok) {} // Constructor
    ~NumNode() {} // Destructor

    void printTok() { NumNodeTok.printToken(); }
};

// Classifies a BINARY OPERATION

class BinOpNode {
private:
    Token BinOpTok;
    std::shared_ptr<GenericNode> LNode;
    std::shared_ptr<GenericNode> RNode; 
public:
    BinOpNode(Token tok, std::shared_ptr<GenericNode> left, std::shared_ptr<GenericNode> right)
        : BinOpTok(tok), LNode(left), RNode(right) {}

    Token getToken() const { return BinOpTok; }
    std::shared_ptr<GenericNode> getLeftNode() const { return LNode; }
    std::shared_ptr<GenericNode> getRightNode() const { return RNode; }
    void printBinOpNode() { std::cout << "(" << LNode->getToken().type_string << " : " << LNode->getToken().text <<
                            BinOpTok.type_string << " : " <<  BinOpTok.text << 
                            RNode->getToken().type_string << " : " << RNode->getToken().text << std::endl; }
                
};

// PARSER CLASS

class Parser {
private:
    std::vector<Token> tokenList;
    std::vector<std::shared_ptr<GenericNode>> classifiedNodes;
    int token_idx = 0;
    Token current_token;

    void advance();
    void parse();
    NumNode factor();
    void term();
    void expr();
public:
    void processTokens(std::vector<Token> tokens) { tokenList = tokens }
    
};

#endif // PARSER_HPP
