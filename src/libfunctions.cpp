#include "globals.hpp"

// file to define extern functions within globals.hpp

void printvec(std::vector<std::string> &s)
{
    for (auto i : s)
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}

#include <string>
#include <vector>
#include <cctype>

std::vector<std::string> splitBySpacesAndBrackets(const std::string &code)
{
    std::vector<std::string> strings;
    std::string currentString;
    bool isSpace = false;
    bool isInComment = false;
    bool isInString = false;
    bool isInChar = false;

    for (size_t i = 0; i < code.length(); ++i)
    {
        char c = code[i];
        if (isInComment)
        {
            currentString += c;
            if (c == '\n')
            {
                strings.push_back(currentString);
                currentString.clear();
                isInComment = false;
            }
            continue;
        }

        if (isInString)
        {
            currentString += c;
            if (c == '\"' || c == '\n')
            {
                strings.push_back(currentString);
                currentString.clear();
                strings.push_back("[newline]");
                currentString.clear();
                isInString = false;
            }
            continue;
        }

        if (c == '\n')
        {
            strings.push_back("[newline]");
            continue;
        }

        if (isInChar)
        {
            currentString += c;
            if (c == '\'')
            {
                strings.push_back(currentString);
                currentString.clear();
                isInChar = false;
            }
            continue;
        }

        if (std::isspace(c))
        {
            if (!currentString.empty())
            {
                strings.push_back(currentString);
                currentString.clear();
            }
            strings.push_back(" ");
            isSpace = true;
            continue;
        }

        if (std::isdigit(c) || (c == '.' && !currentString.empty() && std::isdigit(currentString.back())))
        {
            if (!currentString.empty() && !(std::isdigit(currentString.back()) || currentString.back() == '.'))
            {
                strings.push_back(currentString);
                currentString.clear();
            }
            currentString += c;
            continue;
        }

        if (c == '(' || c == ')' || c == '{' || c == '}' || c == ',' || c == '.' || c == '*' || c == '&')
        {
            if (!currentString.empty())
            {
                strings.push_back(currentString);
                currentString.clear();
            }
            strings.push_back(std::string(1, c));
            isSpace = false;
            continue;
        }

        if (c == '\"')
        {
            if (!currentString.empty())
            {
                strings.push_back(currentString);
                currentString.clear();
            }
            currentString += c;
            isInString = true;
            continue;
        }

        if (c == '\'')
        {
            if (!currentString.empty())
            {
                strings.push_back(currentString);
                currentString.clear();
            }
            currentString += c;
            isInChar = true;
            continue;
        }

        if (c == '/' && i + 1 < code.length() && code[i + 1] == '/')
        {
            if (!currentString.empty())
            {
                strings.push_back(currentString);
                currentString.clear();
            }
            currentString += c;
            isInComment = true;
            continue;
        }

        currentString += c;
        isSpace = false;
    }

    if (!currentString.empty())
    {
        strings.push_back(currentString);
    }

    return strings;
}
