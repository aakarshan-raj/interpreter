#include <string>
#include <iostream>
#include "token.h"
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
    std::vector<std::shared_ptr<Statement>> statements_;
    std::string TokenLiteral() const override;
};

class LetStatement : public Statement
{
    Token token_;
    std::shared_ptr<Identifier> identifier_;
    std::shared_ptr<Expression> value_;
    std::string TokenLiteral() const override;
};

class Identifier : public Expression
{
    Token token_;
    std::string value_;
    std::string TokenLiteral() const override;
};