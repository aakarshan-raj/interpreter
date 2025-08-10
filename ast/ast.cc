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
    return "";
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

std::string BooleanLiteral::TokenLiteral() const
{
    return token_.Literal;
}

std::string BlockStatement::TokenLiteral() const
{
    return token_.Literal;
}

std::string IfExpression::TokenLiteral() const
{
    return token_.Literal;
}

std::string FunctionLiteral::TokenLiteral() const
{
    return token_.Literal;
}

std::string_view Identifier::Type() const
{
    return std::string_view("Identifier");
}

std::string_view IntegerLiteral::Type() const
{
    return std::string_view("IntegerLiteral");
}

std::string_view PrefixExpression::Type() const
{
    return std::string_view("PrefixExpression");
}

std::string_view InfixExpression::Type() const
{
    return std::string_view("InfixExpression");
}

std::string_view LetStatement::Type() const
{
    std::string temp = "LetStatement " + name_->String();
    temp.append(value_->Type());
    return std::string_view(temp);
}

std::string_view ReturnStatement::Type() const
{
    std::string temp = "Return ";
    temp.append(ReturnExpression->Type());
    return std::string_view(temp);
}

std::string_view ExpressionStatement::Type() const
{
    std::string temp = "ExpressionStatement: ";
    temp.append(Expr->Type());
    return std::string_view(temp);
}

std::string_view BooleanLiteral::Type() const
{
    return std::string_view("BooleanLiteral");
}

std::string_view BlockStatement::Type() const
{
    return std::string_view("BlockStatement");
}

std::string_view IfExpression::Type() const
{
    return std::string_view("IfExpression");
}

std::string_view FunctionLiteral::Type() const
{
    return std::string_view("FunctionLiteral");
}

// Implement statement_node

void LetStatement::statement_node() {}
void ReturnStatement::statement_node() {}
void ExpressionStatement::statement_node() {}
void BlockStatement::statement_node() {}

// Implement expression_node
void Identifier::expression_node() {}
void IntegerLiteral::expression_node() {}
void PrefixExpression::expression_node() {}
void InfixExpression::expression_node() {}
void BooleanLiteral::expression_node() {}
void IfExpression::expression_node() {}
void FunctionLiteral::expression_node() {}

// Implement String

std::string Program::String() const
{
    std::ostringstream out;
    for (auto const &stmt : statements_)
    {
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
    out << token_.Literal << " " << name_->String() << " = ";
    if (value_ != nullptr) // we will evaluate expression later
        out << value_->String();
    out << ";";
    return out.str();
}

std::string ReturnStatement::String() const
{
    std::ostringstream out;
    out << token_.Literal << " ";
    if (ReturnExpression != nullptr) // we will evaluate expression later
        out << ReturnExpression->String();
    out << ";";
    return out.str();
}

std::string ExpressionStatement::String() const
{
    if (Expr != nullptr) // we will evaluate expression later
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

std::string BooleanLiteral::String() const
{
    return token_.Literal;
}

std::string BlockStatement::String() const
{
    std::ostringstream out;
    out << "{ ";
    for (const auto &stmt : statements)
    {
        stmt->String();
        out << "\n";
    }
    out << "}";
    return out.str();
}

std::string IfExpression::String() const
{
    std::ostringstream out;
    out << "if ";
    out << condition_->String() << "\n";
    out << consequence_->String();
    if (alternative_ != nullptr)
    {
        out << "else\n";
        out << alternative_->String();
    }
    return out.str();
}

std::string FunctionLiteral::String() const
{
    std::ostringstream out;
    out << TokenLiteral();
    out << "( ";
    for (const std::shared_ptr<Identifier> &x : parameter_)
    {
        out << x->TokenLiteral() << ",";
    }
    out << " )";
    out << "{\n";
    out << body_->String();
    out << "}";

    return out.str();
}