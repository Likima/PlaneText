#include "globals.hpp"
#include "./Parser/parser.hpp"
#include "./Lexer/lexer.hpp"
Lexer lex;
int main()
{
    std::string hello = "hello world! 1 + 1 = 323 testing float 300.0";
    lex.TokenizeLine(hello);
    lex.printTokenized();
    return 0;
}