#include "ast.h"

// Implement TokenLiteral
std::string LetStatement::TokenLiteral() const
{
    return token_.Literal;
}

std::string Identifier::TokenLiteral() const
{
    return token_.Literal;
}

std::string ReturnStatement::TokenLiteral() const
{
    return token_.Literal;
}

std::string Program::TokenLiteral() const
{
    if (!statements_.empty() != 0)
    {
        for (auto &x : statements_)
        {
            std::cout << x->TokenLiteral();
        }
    }
    else
    {
        return "";
    }
}

std::string ExpressionStatement::TokenLiteral() const
{
    return token_.Literal;
}

// Implement statement_node

void LetStatement::statement_node() {}
void Identifier::expression_node() {}
void ReturnStatement::statement_node() {}
void ExpressionStatement::statement_node() {}

// Implement String

std::string Program::String() const
{
    return "";
}

std::string Identifier::String() const
{
    return value_;
}

std::string LetStatement::String() const
{
    std::ostringstream out;
    out << token_.Literal << name_->String() << " = ";
    if (value_ != nullptr)
        out << value_->String();
    out << ";";
    return out.str();
}

std::string ReturnStatement::String() const
{
    std::ostringstream out;
    out << token_.Literal << " ";
    if (ReturnExpression != nullptr)
        out <<ReturnExpression->String();
    out << ";";
    return out.str();
}

std::string ExpressionStatement::String() const
{
    if (Expr != nullptr)
        return Expr->String();
    return "";
}