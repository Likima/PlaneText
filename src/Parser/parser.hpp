#ifndef PARSER_HPP
#define PARSER_HPP

//#include "../Lexer/lexer.hpp"
#include "../globals.hpp"

#include <variant>
#include <memory>

struct LiteralExpr;
struct VariableExpr;
struct UnaryExpr;
struct BinaryExpr;
struct IfExpr;

using Expr = std::variant<LiteralExpr, VariableExpr, UnaryExpr, BinaryExpr, IfExpr>;
using ExprHandle = std::unique_ptr<Expr>;

//struct LiteralExpr {
//  Literal lit;
//};
//
//struct VariableExpr {
//  std::string ident;
//};
//
//struct UnaryExpr {
//  UnaryOp op;
//  ExprHandle expr;
//};
//
//struct BinaryExpr {
//  BinaryOp op;
//  ExprHandle lhs;
//  ExprHandle rhs;
//};
//
//struct IfExpr {
//  ExprHandle cond_expr;
//  ExprHandle if_expr;
//  ExprHandle else_expr;
//};

#endif