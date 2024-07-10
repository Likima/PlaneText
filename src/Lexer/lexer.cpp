#include "lexer.hpp"

const std::vector<std::pair<TokenType, std::regex>> TokenDefinitions = {
    {DATATYPE, std::regex("\\b(int|float|double|char|bool|long)\\b")},
    {KEYWORD, std::regex("\\b(if|else|for|while|return|auto|break|case|const|"
                         "continue|default|do|enum|extern|goto|register|short|signed|"
                         "sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|alignas|alignof|"
                         "and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|bitand|bitor|catch|"
                         "char16_t|char32_t|char8_t|class|co_await|co_return|co_yield|compl|concept|const_cast|"
                         "consteval|constexpr|constinit|decltype|delete|dynamic_cast|explicit|export|friend|"
                         "inline|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|"
                         "protected|public|reflexpr|reinterpret_cast|requires|static_assert|static_cast|synchronized|"
                         "template|this|thread_local|throw|try|typeid|typename|using|virtual|wchar_t|xor|xor_eq)\\b")},
    {IDENTIFIER, std::regex("\\b[a-zA-Z_][a-zA-Z0-9_]*\\b")},
    {TT_STRING, std::regex("\"[^\"]*\"|'[^']*'\\b")},
    {TT_BOOL, std::regex("\\b(true|false)\\b")},
    {TT_INT, std::regex("\\b[0-9]+\\b")},
    {TT_FLOAT, std::regex("\\b([0-9]*\\.[0-9]+|[0-9]+\\.[0-9]*)\\b")},
    {TT_ADD, std::regex("\\+")},
    {TT_SUB, std::regex("\\-")},
    {TT_MUL, std::regex("\\*")},
    {TT_DIV, std::regex("\\/")},
    {TT_EQL, std::regex("\\=")},
    {TT_LPAREN, std::regex("\\(")},
    {TT_RPAREN, std::regex("\\)")},
    {TT_LBRACE, std::regex("\\{")},
    {TT_RBRACE, std::regex("\\}")},
    {TT_LBRACK, std::regex("\\[")},
    {TT_RBRACK, std::regex("\\]")},
    {TT_COMMA, std::regex("\\,")},
    {TT_PERIOD, std::regex("\\.")},
    {TT_GTR, std::regex("\\>")},
    {TT_LST, std::regex("\\<")},
    {TT_NOT, std::regex("\\!")},
    {TT_NULL, std::regex("\\b(null)\\b")},
    {COMMENT, std::regex("//[^\n]*$")},
    {NEWLINE, std::regex("[newline]|;")},
    {UNKNOWN, std::regex("")}
};


void Lexer::printTokenized()
{
    for (const auto &i : tokenized_code)
    {
        std::string type = "REFACTORING"; // change later
        switch (i.type)
        {
            case DATATYPE: type = "datatype"; break;
            case KEYWORD: type = "keyword"; break;
            case IDENTIFIER: type = "identifier"; break;
            case TT_STRING: type = "string"; break;
            case TT_INT: type = "number"; break;
            case TT_FLOAT: type = "float"; break;
            case TT_ADD:
            case TT_SUB:
            case TT_MUL:
            case TT_DIV:
            case TT_EQL: 
            case TT_GTR:
            case TT_LST:
            case TT_NOT:
                type = "operator"; break;
            case TT_LPAREN:
            case TT_RPAREN:
            case TT_LBRACE:
            case TT_RBRACE:
            case TT_LBRACK:
            case TT_RBRACK:
            case TT_COMMA:
            case TT_PERIOD: 
                type = "delimiter"; break;
            case TT_NULL: type = "literal"; break;
            case COMMENT: type = "comment"; break;
            case NEWLINE: type = "newline"; break;
            case UNKNOWN: type = "undefined"; break;
            default: type = "undefined";
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