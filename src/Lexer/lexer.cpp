#include "lexer.hpp"

const std::vector<std::pair<TokenType, std::regex>> TokenDefinitions = {
    {KEYWORD, std::regex("\\b(if|else|for|while|return|auto|break|case|char|const|"
                         "continue|default|do|double|enum|extern|float|goto|int|long|register|short|signed|"
                         "sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|alignas|alignof|"
                         "and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|bitand|bitor|bool|catch|"
                         "char16_t|char32_t|char8_t|class|co_await|co_return|co_yield|compl|concept|const_cast|"
                         "consteval|constexpr|constinit|decltype|delete|dynamic_cast|explicit|export|false|friend|"
                         "inline|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|"
                         "protected|public|reflexpr|reinterpret_cast|requires|static_assert|static_cast|synchronized|"
                         "template|this|thread_local|throw|true|try|typeid|typename|using|virtual|wchar_t|xor|xor_eq)\\b")},
    {IDENTIFIER, std::regex("\\b[a-zA-Z_][a-zA-Z0-9_]*\\b")},
    {NUMBER, std::regex("\\b[0-9]+|#include\\b")},
    {STRING, std::regex("\"[^\"]*\"|'[^']*'")},
    {OPERATOR, std::regex("[+\\-*/=]")},
    {DELIMITER, std::regex("[(){};] ")},
    {COMMENT, std::regex("//[^\n]*$")},
    {NEWLINE, std::regex("[newline]")}};

void Lexer::printTokenized()
{
    std::string type;
    for (auto &i : tokenized_code)
    {
        switch (i.type)
        {
        case (KEYWORD):
        {
            type = "keyword";
        }
        break;
        case (IDENTIFIER):
        {
            type = "identifier";
        }
        break;
        case (NUMBER):
        {
            type = "number";
        }
        break;
        case (STRING):
        {
            type = "string";
        }
        break;
        case (OPERATOR):
        {
            type = "operator";
        }
        break;
        case (DELIMITER):
        {
            type = "delimiter";
        }
        break;
        case (COMMENT):
        {
            type = "comment";
        }
        break;
        case (NEWLINE):
        {
            type = "newline";
        }
        break;
        default:
        {
            type = "UNDEFINED";
        }
        }
        std::cout << "TYPE: " << type << " TEXT: " << i.text << std::endl;
    }
}

Token tokenizeSingleWord(const std::string &word)
{
    for (const auto &definition : TokenDefinitions)
    {
        if (std::regex_match(word, definition.second))
        {
            return {definition.first, word};
        }
    }
    // Default case if no match found
    return {UNKNOWN, word}; // Assuming it's an identifier if not matched (CLASSIFIES SPACES)
}

void Lexer::TokenizeLine(std::string &code)
{
    std::sregex_iterator end;
    std::vector<std::string> split_vec = splitBySpacesAndBrackets(code);
    printvec(split_vec);
    for (const auto &word : split_vec)
    {
        Token t = tokenizeSingleWord(word);
        if (t.type != UNKNOWN)
            tokenized_code.push_back(t);
    }
}