#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

extern std::vector<std::string> splitBySpacesAndBrackets(const std::string &code);

extern void printvec(std::vector<std::string> &s);

#endif