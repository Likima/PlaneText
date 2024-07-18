#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <memory>
#include <variant>
#include "../globals.hpp"
#include "../Lexer/lexer.hpp"
#include "../Parser/parser.hpp"

class Interpreter {
private:
    std::shared_ptr<GenericNode> ast;
    std::shared_ptr<Error> err = nullptr;
public:
    Interpreter() = default; // default constructor
    explicit Interpreter(std::shared_ptr<GenericNode> b) : ast(b) {} // non-default constructor with initialization list
    ~Interpreter() = default; // default destructor

    void Advance();
    void setErr(std::shared_ptr<Error> e);
    std::variant<int, float> InterpretNum(std::shared_ptr<GenericNode> current_node = nullptr);
    bool Interpret(std::shared_ptr<GenericNode> current_node = nullptr);

    // make sure to INVOKE interpretation of specific datatypes etc. using a caller function.
};

#endif // INTERPRETER_HPP
