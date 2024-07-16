#include "globals.hpp"
#include "./Parser/parser.hpp"
#include "./Lexer/lexer.hpp"

std::vector<std::string> lines = {};

bool read_from_file(std::string &file_name)
{

    // Validate the filename
    if (file_name.empty())
    {
        std::cerr << "Invalid file name" << std::endl;
        return false;
    }

    // Open the file
    std::ifstream file(file_name);
    if (!file.is_open())
        return false;

    // Read each line from the file and add it to e.lines vector
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }

    if (lines.size() > 0 && lines[0].empty())
    {
        if (lines.empty())
        {
            lines.erase(lines.begin());
        }
    }

    // Close the file
    file.close();
    return true;
}

int main(int argc, char **argv)
{
    std::string save_file;
    if (argc >= 2)
    {
        save_file = argv[1];
        if (!read_from_file(save_file))
        {
            std::cout << "File Name Invalid" << std::endl;
            return -1;
        }
    }
    std::vector<Token> tokenized;
    // std::string hello = "4 + 3 * 5 * 3 + 5";
    Lexer lex(lines);
    Parser par;
    lex.printLexer();
    std::cout << std::endl;
    par.parse(lex.getTokenizedCode());
    return 0;
}