#include "errors.hpp"

// TODO: send a line and print arrows underneath the actual error

void printErrLines(int x_pos, int y_pos)
{
    std::cout << lines[y_pos] << std::endl;
    for (int x = 0; x < x_pos; x++)
    {
        std::cout << "-";
    }
    std::cout << "^ HERE" << std::endl;
}

void Error::printErr() const
{
    std::string result;
    result = error_name + ": " + details + "\n";
    result += "LINE " + std::to_string(pos_start + 1) + " POSITION " + std::to_string(pos_end);
    std::cout << result << std::endl;
    printErrLines(pos_end, pos_start);
}