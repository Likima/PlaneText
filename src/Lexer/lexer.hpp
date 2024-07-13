#ifndef LEXER_HPP
#define LEXER_HPP

#include <regex>
#include "../globals.hpp"
#include <variant>
#include <string>

enum TokenType
{
    DATATYPE,
    KEYWORD,
    IDENTIFIER,
    TT_STRING,
    TT_BOOL,
    TT_NULL,
    TT_INT,
    TT_FLOAT,
    TT_ADD,
    TT_SUB,
    TT_MUL,
    TT_DIV,
    TT_EQL,
    TT_LPAREN,
    TT_RPAREN,
    TT_LBRACE,
    TT_RBRACE,
    TT_LBRACK,
    TT_RBRACK,
    TT_COMMA,
    TT_PERIOD,
    TT_GTR,
    TT_LST,
    TT_NOT,
    DELIMITER,
    COMMENT,
    NEWLINE,
    UNKNOWN
};

class Token
{
private:
    int startpos, endpos;

public:
    TokenType type;
    std::string text;
    std::string type_string;
    void printToken() const { std::cout << type_string << ": " << text << std::endl; }
    void printTokenWithoutEndl() const { std::cout << type_string << ": " << text << ", "; }

    Token(int startpos = -1, int endpos = -1)
    {
        if (startpos != -1 && endpos != -1)
        {
            this->startpos = startpos;
            this->endpos = endpos;
        }
    };
    Token(TokenType t, std::string s, int startpos = -1, int endpos = -1) : type(t), text(s)
    {
        if (startpos != -1 && endpos != -1)
        {
            this->startpos = startpos;
            this->endpos = endpos;
        }
    };
};

class Lexer
{
private:
    std::vector<Token> tokenized_code;

public:
    Lexer(){};
    Lexer(std::vector<std::string> s)
    {
        for (auto &i : s)
        {
            for (auto &n : TokenizeLine(i))
            {
                tokenized_code.push_back(n);
            }
        }
    }
    void assignTokenizedString();
    void printLexer();
    std::vector<Token> getTokenizedCode() { return tokenized_code; }
    std::vector<Token> TokenizeLine(std::string &code);
};

#endif