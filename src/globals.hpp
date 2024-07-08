#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <iostream>
#include <vector>
#include <string>

enum TokenType
{
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    STRING,
    OPERATOR,
    DELIMITER,
    COMMENT,
    UNKNOWN
};

struct Token
{
    TokenType type;
    std::string text;
};

class Lexer {
    private:
        
    public:
        std::vector<Token> tokenized_code;
};

extern Lexer lex;

#endif