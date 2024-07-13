#include "globals.hpp"
#include "./Parser/parser.hpp"
#include "./Lexer/lexer.hpp"
Lexer lex;
Parser par;
int main()
{
    std::vector<Token> tokenized;
    std::string hello = "4 + 3 * 5 * 3 + 5";
    tokenized = lex.TokenizeLine(hello);
    lex.printLexer();
    std::cout << std::endl;
    par.parse(tokenized);
    return 0;
}