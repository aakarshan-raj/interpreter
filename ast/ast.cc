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

std::string IntegerLiteral::TokenLiteral() const
{
    return token_.Literal;
}

std::string PrefixExpression::TokenLiteral() const
{
    return token_.Literal;
}

std::string InfixExpression::TokenLiteral() const
{
    return token_.Literal;
}


// Implement statement_node

void LetStatement::statement_node() {}
void ReturnStatement::statement_node() {}
void ExpressionStatement::statement_node() {}

// Implement expression_node
void Identifier::expression_node() {}
void IntegerLiteral::expression_node() {}
void PrefixExpression::expression_node() {}
void InfixExpression::expression_node() {}


// Implement String

std::string Program::String() const
{
    std::ostringstream out;
    for(auto const &stmt:statements_){
        out << stmt->String();
    }
    return out.str();
}

std::string Identifier::String() const
{
    return value_;
}

std::string LetStatement::String() const
{
    std::ostringstream out;
    out << token_.Literal << " "<<name_->String() << " = ";
    if (value_ != nullptr)            // we will evaluate expression later
        out << value_->String();
    out << ";";
    return out.str();
}

std::string ReturnStatement::String() const
{
    std::ostringstream out;
    out << token_.Literal << " ";
    if (ReturnExpression != nullptr)    // we will evaluate expression later
        out <<ReturnExpression->String();
    out << ";";
    return out.str();
}

std::string ExpressionStatement::String() const
{
    if (Expr != nullptr)              // we will evaluate expression later
        return Expr->String();
    return "";
}

std::string IntegerLiteral::String() const
{
    return token_.Literal;
}

std::string PrefixExpression::String() const
{
    std::ostringstream out;
    out << "(" << op;
    if (right != nullptr)
        out << right->String();
    out << ")";
    return out.str();
}

std::string InfixExpression::String() const
{
    std::ostringstream out;
    out << "(";
    if (left != nullptr)
        out << left->String();
    out << " ";
    out << op;
    out << " ";
    if (right != nullptr)
        out << right->String();
    out << ")";
    return out.str();
}