#include "globals.hpp"
#include "./Lexer/lexer.hpp"

Lexer lex;

int main()
{
    std::string helloworld = "\"Hello world\" +\n  HELLO";
    lex.TokenizeLine(helloworld);
    lex.printTokenized();
}