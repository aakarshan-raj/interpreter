#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../parser/parser.h"


bool TestIdetifier(std::shared_ptr<Expression> iden_, std::string value_)
{
    auto idenOp = std::dynamic_pointer_cast<Identifier>(iden_);
    EXPECT_NE(idenOp, nullptr) << "Expected this expression to be a Identifier, is not.";

    EXPECT_EQ(idenOp->value_, value_) << "Identifier value is not same. Expected:" << value_ << " Got:" << idenOp->value_;

    EXPECT_EQ(idenOp->TokenLiteral(), value_) << "IntegerLiteral TokenLiteral() is not same. Expected:" << value_ << " Got:" << idenOp->TokenLiteral();
}
bool TestIntegerLiteral(std::shared_ptr<Expression> intL, int value_)
{
    auto inteOp = std::dynamic_pointer_cast<IntegerLiteral>(intL);
    EXPECT_NE(inteOp, nullptr) << "Expected this expression to be a integerLiteral, is not.";

    EXPECT_EQ(inteOp->value_, value_) << "IntegerLiteral value is not same. Expected:" << value_ << " Got:" << inteOp->value_;

    EXPECT_EQ(inteOp->TokenLiteral(), std::to_string(value_)) << "IntegerLiteral TokenLiteral() is not same. Expected:" << value_ << " Got:" << inteOp->TokenLiteral();
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