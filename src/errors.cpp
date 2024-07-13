#include "errors.hpp"

void Error::printErr()
{
    std::string result;
    result = error_name + ": " + details + "\n";
    result += std::to_string(pos_start) + " " + std::to_string(pos_end);
    std::cout << result << std::endl;
}