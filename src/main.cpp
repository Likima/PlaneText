#include "globals.hpp"
#include "./Parser/parser.hpp"
#include "./Lexer/lexer.hpp"
#include "./Interpreter/interpreter.hpp"

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
    //========================
    // INITIAL DECLARATIONS
    //========================

    std::string save_file;
    std::vector<Token> tokenized;

    //========================
    // READ FROM FILE
    //========================

    if (argc >= 2)
    {
        save_file = argv[1];
        if (!read_from_file(save_file))
        {
            std::cout << "File Name Invalid" << std::endl;
            return -1;
        }
    }

    //========================
    // INSTANTIATE CLASSES
    //========================

    Lexer lex(lines);
    Parser par;
    lex.printLexer();
    std::cout << std::endl;
    if (!par.parse(lex.getTokenizedCode()))
    {
        std::cout << "Compilation terminated due to errors. " << std::endl;
        return -1;
    }
    Interpreter inter(par.getAST());
    std::cout<<std::get<int>(inter.Interpret())<<std::endl;
    return 0;
}