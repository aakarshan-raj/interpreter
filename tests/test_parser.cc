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

TEST(Parser, BasicTest)
{

    std::string input = R""""(
let x = 5;
let y = 10;
let foobar = 838383;
let a = 3;
    )"""";

    std::vector<std::string> identifers = {"x", "y", "foobar"};

    std::shared_ptr<Lexer> lexer = std::make_shared<Lexer>(input);
    std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
    std::shared_ptr<Program> program = parser->parseProgram();

    EXPECT_NE(program, nullptr) << "Program is null.";
    EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";

    for (int i = 0; i < identifers.size(); i++)
    {
        TestLetStatements(program->statements_[i], identifers[i]);
    }

    checkForParserErrors(parser);
}

TEST(Parser, ReturnStatementTest)
{

    std::string input = R""""(
return x;
return 10;
return 53458934;
    )"""";

    std::shared_ptr<Lexer>
        lexer = std::make_shared<Lexer>(input);
    std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
    std::shared_ptr<Program> program = parser->parseProgram();

    EXPECT_NE(program, nullptr) << "Program is null.";
    EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";
    EXPECT_EQ(program->statements_.size(), 3) << "Program doesn't contain 3 statements as expected.";

    for (const auto &stmt : program->statements_)
    {
        auto returnStmt = std::dynamic_pointer_cast<ReturnStatement>(stmt);
        EXPECT_EQ(returnStmt->TokenLiteral(), "return") << "Return tokenLiteral expected: return, got: " << returnStmt->TokenLiteral();
    }

    checkForParserErrors(parser);
}

TEST(Parser, IdentiferExpressionTest)
{

    std::string input = "foobar;";

    std::shared_ptr<Lexer>
        lexer = std::make_shared<Lexer>(input);
    std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
    std::shared_ptr<Program> program = parser->parseProgram();

    EXPECT_NE(program, nullptr) << "Program is null.";
    EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";
    EXPECT_EQ(program->statements_.size(), 1) << "Program doesn't contain 1 statements as expected.";

    auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(program->statements_[0]);

    EXPECT_NE(expressionStatement, nullptr) << "Expected this statement to be a expression statement, is not.";

    auto identifier = std::dynamic_pointer_cast<Identifier>(expressionStatement->Expr);

    EXPECT_NE(identifier, nullptr) << "Expected this expression to be a an identifier, is not.";
    EXPECT_EQ(identifier->value_, "foobar") << "identifier expected: " << input << " , got: " << identifier->value_;
    EXPECT_EQ(identifier->TokenLiteral(), "foobar") << "identifier.TokenLiteral expected: " << input << " , got: " << identifier->value_;

    checkForParserErrors(parser);
}


TEST(Parser, IntegerExpressionTest)
{

    std::string input = "5";

    std::shared_ptr<Lexer>
        lexer = std::make_shared<Lexer>(input);
    std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
    std::shared_ptr<Program> program = parser->parseProgram();

    EXPECT_NE(program, nullptr) << "Program is null.";
    EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";
    EXPECT_EQ(program->statements_.size(), 1) << "Program doesn't contain 1 statements as expected.";

    auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(program->statements_[0]);

    EXPECT_NE(expressionStatement, nullptr) << "Expected this statement to be a expression statement, is not.";

    auto identifier = std::dynamic_pointer_cast<Identifier>(expressionStatement->Expr);

    EXPECT_NE(identifier, nullptr) << "Expected this expression to be a an identifier, is not.";
    EXPECT_EQ(identifier->value_, "foobar") << "identifier expected: " << input << " , got: " << identifier->value_;
    EXPECT_EQ(identifier->TokenLiteral(), "foobar") << "identifier.TokenLiteral expected: " << input << " , got: " << identifier->value_;

    checkForParserErrors(parser);
}
