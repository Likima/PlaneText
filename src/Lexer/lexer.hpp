#ifndef LEXER_HPP
#define LEXER_HPP

#include <regex>
#include "../globals.hpp"
#include <variant>
#include <string>

enum TokenType
{
    DATATYPE, KEYWORD, IDENTIFIER,
    TT_STRING, TT_BOOL, TT_NULL,
    TT_INT, TT_FLOAT, TT_ADD,
    TT_SUB, TT_MUL, TT_DIV,
    TT_EQL, TT_LPAREN, TT_RPAREN,
    TT_LBRACE, TT_RBRACE, TT_LBRACK,
    TT_RBRACK, TT_COMMA, TT_PERIOD,
    TT_GTR, TT_LST, TT_NOT,
    DELIMITER, COMMENT,
    NEWLINE, UNKNOWN
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