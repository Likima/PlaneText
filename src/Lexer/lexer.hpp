#ifndef LEXER_HPP
#define LEXER_HPP

#include <regex>
#include "../globals.hpp"

enum TokenType
{
    DATATYPE,
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    STRING,
    OPERATOR,
    DELIMITER,
    COMMENT,
    NEWLINE,
    UNKNOWN
};

struct Token
{
    TokenType type;
    std::string text;
};

class Lexer
{
private:
    std::vector<Token> tokenized_code;

public:
    void printTokenized();
    void TokenizeLine(std::string &code);
};

#endif