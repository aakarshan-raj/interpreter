#ifndef AST_H
#define AST_H

#include <string>
#include <iostream>
#include "../token/token.h"
#include <memory>
#include <vector>

class Node
{

public:
    virtual std::string TokenLiteral() const = 0;
    virtual ~Node() = default;
};

class Statement : public Node
{
    virtual void statement_node() = 0;
};

class Expression : public Node
{
    virtual void expression_node() = 0;
};

class Program : public Node
{
public:
    std::vector<std::shared_ptr<Statement>> statements_;
    std::string TokenLiteral() const override;
};

class Identifier : public Expression
{
public:
    Token token_;
    std::string value_;
    std::string TokenLiteral() const override;
};
class LetStatement : public Statement
{
public:
    Token token_;
    std::shared_ptr<Identifier> name_;
    std::shared_ptr<Expression> value_;
    std::string TokenLiteral() const override;
};

#endif