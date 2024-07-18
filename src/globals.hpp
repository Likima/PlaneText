#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <variant>


extern std::vector<std::string> lines;

extern std::vector<std::string> splitBySpacesAndBrackets(const std::string &code);

extern void printvec(std::vector<std::string> &s);

#endif