#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <memory>
#include <variant>
#include "../Lexer/lexer.hpp"
#include "../Parser/parser.hpp"

class Interpreter {
private:
    std::shared_ptr<GenericNode> ast;

public:
    Interpreter() = default; // default constructor
    explicit Interpreter(std::shared_ptr<GenericNode> b) : ast(b) {} // non-default constructor with initialization list
    ~Interpreter() = default; // default destructor

    void Advance();
    std::variant<int, float> Interpret(std::shared_ptr<GenericNode> current_node = nullptr) const; // const-correctness
};

#endif // INTERPRETER_HPP
