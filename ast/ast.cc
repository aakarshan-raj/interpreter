#include "ast.h"

std::string LetStatement::TokenLiteral() const
{
    return token_.Literal;
}

std::string Identifier::TokenLiteral() const
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
