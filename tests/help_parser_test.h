#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../parser/parser.h"
#include <any>
#include <typeinfo>

bool TestIdetifier(std::shared_ptr<Expression> iden_, std::string value_)
{
    auto idenOp = std::dynamic_pointer_cast<Identifier>(iden_);
    if (!idenOp)
    {
        std::cerr << "Expected this expression to be a Identifier, is not.";
        return false;
    }
    if (idenOp->value_ != value_)
    {
        std::cerr << "Identifier value is not same. Expected:" << value_ << " Got:" << idenOp->value_ << "\n";
        return false;
    }
    if (idenOp->TokenLiteral() != value_)
    {
        std::cerr << "IntegerLiteral TokenLiteral() is not same. Expected:" << value_ << " Got:" << idenOp->TokenLiteral() << "\n";
        return false;
    }
    return true;
}

bool TestIntegerLiteral(std::shared_ptr<Expression> intL, int value_)
{
    auto inteOp = std::dynamic_pointer_cast<IntegerLiteral>(intL);
    if (!inteOp)
    {
        std::cerr << "Expected this expression to be a Identifier, is not.";
        return false;
    }
    if (inteOp->value_ != value_)
    {
        std::cerr << "Identifier value is not same. Expected:" << value_ << " Got:" << inteOp->value_ << "\n";
        return false;
    }
    if (inteOp->TokenLiteral() != std::to_string(value_))
    {
        std::cerr << "IntegerLiteral TokenLiteral() is not same. Expected:" << value_ << " Got:" << inteOp->TokenLiteral() << "\n";
        return false;
    }
    return true;
}

void TestLetStatements(std::shared_ptr<Statement> s, std::string variable_name)
{

    if (s->TokenLiteral() != "let")
    {
        FAIL() << "Wrong Let token literal\nExpected:let" << "Got:" << s->TokenLiteral();
    }
    std::shared_ptr<LetStatement> lstmt = std::dynamic_pointer_cast<LetStatement>(s);

    if (lstmt->name_->value_ != variable_name)
    {
        FAIL() << "Wrong Variable literal\nExpected:" << variable_name << "Got:" << lstmt->name_->value_;
    }
    if (lstmt->name_->TokenLiteral() != variable_name)
    {
        FAIL() << "Wrong Variable literal\nExpected:" << variable_name << "Got:" << lstmt->name_->value_;
    }
}

void checkForParserErrors(std::shared_ptr<Parser> parser)
{
    std::vector<std::string> errors = parser->logErrors();
    if (errors.size() == 0)
    {
        return;
    }
    else
    {
        for (const std::string &error : errors)
        {
            FAIL() << error << std::endl;
        }
    }
}

std::string typeInfo(const std::any &value)
{
    const std::type_info &type = value.type();

    if (type == typeid(int))
    {
        return "INT";
    }
    else if (type == typeid(std::string))
    {
        return "STRING";
    }
    else if (type == typeid(const char *))
    {
        return "STRING";
    }
    return "UNKNOWN";
}

bool testLiteralExpression(std::shared_ptr<Expression> expr, std::any &expected)
{
    std::string_view x = (typeInfo(expected));
    if (x == "INT")
    {
        return TestIntegerLiteral(expr, std::any_cast<int>(expected));
    }
    else if (x == "STRING")
    {
        return TestIdetifier(expr, std::any_cast<std::string>(expected));
    }
    else
    {
        return false;
    }
}

bool testInfixExpression(std::shared_ptr<Expression> expr, std::any left, std::string op, std::any right)
{
    auto infixExpr = std::dynamic_pointer_cast<InfixExpression>(expr);
    if (!infixExpr)
    {
        std::cerr << "Not a infixExpression\n";
        return false;
    }

    // Test Left side of expr
    if (!testLiteralExpression(infixExpr->left, left))
    {
        std::cerr << "Left expression failure\n";
        return false;
    }

    if (op != infixExpr->op)
    {
        std::cerr << "Operand expected: " << op << " Got:" << infixExpr->op << "\n";
        return false;
    }
    // Test Right side of expr
    if (!testLiteralExpression(infixExpr->right, right))
    {
        std::cerr << "Right expression failure\n";
        return false;
    }
    return true;
}
