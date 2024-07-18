#ifndef LEXER_HPP
#define LEXER_HPP

#include "../globals.hpp"

#include <regex>
#include <variant>

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
    std::string type_string; // TODO: This is scuffed. Make private if time permits and add get/set functions.
    void printToken() const { std::cout << type_string << ": " << text << std::endl; }
    void printTokenWithoutEndl() const { std::cout << " " << type_string << ": " << text; }
    std::pair<int, int> getPos() { return std::make_pair(startpos, endpos); }

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
    int row = 0;
    int col = 0;
public:
    Lexer(){};
    Lexer(std::vector<std::string> s) { for (auto &i : s) TokenizeLine(i); }
    void assignTokenizedString();
    void printLexer();
    std::vector<Token> getTokenizedCode() { return tokenized_code; }
    std::vector<Token> TokenizeLine(const std::string &code);
};

#endif