#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include <memory>

void TestLetStatements(std::shared_ptr<Statement> s, std::string variable_name)
{
    // LET statement
    // LET(Token) x(Identifier) = value(Expression);

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

TEST(Paser, BasicTest)
{

    std::string input = R""""(
let x = 5;
let y = 10;
let foobar = 838383;
    )"""";

    std::vector<std::string> identifers = {"x", "y", "foobar"};

    std::shared_ptr<Lexer>
        lexer = std::make_shared<Lexer>(input);
    Parser parser(lexer);

    std::shared_ptr<Program> program = parser.ParseProgram();

    if (program == nullptr)
    {
        FAIL() << "Program is null.";
    }

    if (program->statements_.empty())
    {
        FAIL() << "Program has no statements.";
    }

    for (int i = 0; i < identifers.size(); i++)
    {
        TestLetStatements(program->statements_[i], identifers[i]);
    }
}
