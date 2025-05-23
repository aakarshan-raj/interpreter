#ifndef AST_H
#define AST_H

#include <string>
#include <iostream>
#include "../token/token.h"
#include <memory>
#include <vector>
#include <sstream>

class Node
{

public:
    virtual std::string TokenLiteral() const = 0;
    virtual std::string String() const = 0;
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
    std::string String() const override;
};

class Identifier : public Expression
{
public:
    Identifier(const Token& t):token_(t),value_(t.Literal){}
    Token token_;
    std::string value_;
    std::string TokenLiteral() const override;
    void expression_node() override;
    std::string String() const override;

};
class LetStatement : public Statement
{
public:
    LetStatement(const Token& t):token_(t){}
    Token token_;
    std::shared_ptr<Identifier> name_;
    std::shared_ptr<Expression> value_;
    std::string TokenLiteral() const override;
    void statement_node() override;
    std::string String() const override;

};

class ReturnStatement: public Statement{
    public:
    ReturnStatement(const Token &t):token_(t){}
    Token token_;
    std::shared_ptr<Expression> ReturnExpression;
    std::string TokenLiteral() const override;
    void statement_node() override;
    std::string String() const override;

};

class ExpressionStatement: public Statement{
    public:
    ExpressionStatement(const Token &t):token_(t){}
    Token token_;
    std::shared_ptr<Expression> Expr;
    std::string TokenLiteral() const override;
    void statement_node() override;
    std::string String() const override;

};

class IntegerLiteral : public Expression
{
public:
    IntegerLiteral(const Token& t):token_(t){}
    Token token_;
    int value_;
    std::string TokenLiteral() const override;
    void expression_node() override;
    std::string String() const override;

};

class PrefixExpression : public Expression
{
public:
    PrefixExpression(const Token& t):token_(t){}
    Token token_;
    std::string op;
    std::shared_ptr<Expression> right;
    std::string TokenLiteral() const override;
    void expression_node() override;
    std::string String() const override;

};

class InfixExpression : public Expression
{
public:
    InfixExpression(const Token& t):token_(t){}
    Token token_;
    std::string op;
    std::shared_ptr<Expression> right;
    std::shared_ptr<Expression> left;
    std::string TokenLiteral() const override;
    void expression_node() override;
    std::string String() const override;

};

#endif