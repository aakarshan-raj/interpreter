#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include <memory>
#include "help_parser_test.h"

TEST(Parser, BasicTest)
{

    std::string input = R""""(
let x = 5;
let y = 10;
let foobar = 838383;
let a = 3;
    )"""";

    std::vector<std::string> identifiers = {"x", "y", "foobar"};

    std::shared_ptr<Lexer> lexer = std::make_shared<Lexer>(input);
    std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
    std::shared_ptr<Program> program = parser->parseProgram();

    EXPECT_NE(program, nullptr) << "Program is null.";
    EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";

    for (int i = 0; i < identifiers.size(); i++)
    {
        TestLetStatements(program->statements_[i], identifiers[i]);
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

TEST(Parser, identifierExpressionTest)
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
    EXPECT_EQ(identifier->TokenLiteral(), "foobar") << "identifier.TokenLiteral expected: " << input << " , got: " << identifier->TokenLiteral();

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

    auto intLiteral = std::dynamic_pointer_cast<IntegerLiteral>(expressionStatement->Expr);

    EXPECT_NE(intLiteral, nullptr) << "Expected this expression to be a an IntegerLiteral, is not.";
    EXPECT_EQ(intLiteral->value_, 5) << "Integer literal expected: " << 5 << " , got: " << intLiteral->value_;
    EXPECT_EQ(intLiteral->TokenLiteral(), "5") << "IntegerLiteral.TokenLiteral expected: " << input << " , got: " << intLiteral->TokenLiteral();

    checkForParserErrors(parser);
}

TEST(Parser, PrefixExpressionTest)
{

    struct PrefixExpressionTestStruct
    {
        std::string expr;
        std::string op;
        int integerLiteral;
    };

    std::vector<PrefixExpressionTestStruct> input = {{"!5", "!", 5}, {"-15", "-", 15}};

    for (auto const &ex : input)
    {

        std::shared_ptr<Lexer>
            lexer = std::make_shared<Lexer>(ex.expr);
        std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
        std::shared_ptr<Program> program = parser->parseProgram();

        EXPECT_NE(program, nullptr) << "Program is null.";
        EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";

        EXPECT_EQ(program->statements_.size(), 1) << "Program doesn't contain 1 statements as expected.";

        checkForParserErrors(parser);

        auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(program->statements_[0]);

        EXPECT_NE(expressionStatement, nullptr) << "Expected this statement to be a expression statement, is not.";

        auto prefixOp = std::dynamic_pointer_cast<PrefixExpression>(expressionStatement->Expr);

        EXPECT_NE(prefixOp, nullptr) << "Expected this expression to be a an PrefixExpression, is not.";
        EXPECT_EQ(prefixOp->op, ex.op) << "PrefixExpression operator expected: " << ex.op << " , got: " << prefixOp->op;
        EXPECT_TRUE(TestIntegerLiteral(prefixOp->right, ex.integerLiteral))<<"TestIntegerLiteral FAIL";
    }
}

TEST(Parser, PrefixExpressionTestRightExpressionidentifier)
{

    struct PrefixExpressionTestStruct
    {
        std::string expr;
        std::string op;
        std::string variable_name_;
    };

    std::vector<PrefixExpressionTestStruct> input = {{"!var", "!", "var"}, {"-abc", "-", "abc"}};

    for (auto const &ex : input)
    {

        std::shared_ptr<Lexer>
            lexer = std::make_shared<Lexer>(ex.expr);
        std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
        std::shared_ptr<Program> program = parser->parseProgram();

        EXPECT_NE(program, nullptr) << "Program is null.";
        EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";

        EXPECT_EQ(program->statements_.size(), 1) << "Program doesn't contain 1 statements as expected.";

        checkForParserErrors(parser);

        auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(program->statements_[0]);

        EXPECT_NE(expressionStatement, nullptr) << "Expected this statement to be a expression statement, is not.";

        auto prefixOp = std::dynamic_pointer_cast<PrefixExpression>(expressionStatement->Expr);

        EXPECT_NE(prefixOp, nullptr) << "Expected this expression to be a an PrefixExpression, is not.";
        EXPECT_EQ(prefixOp->op, ex.op) << "PrefixExpression operator expected: " << ex.op << " , got: " << prefixOp->op;
        EXPECT_TRUE(TestIdetifier(prefixOp->right, ex.variable_name_)) << "TestIdetifier Fail\n";
    }
}

TEST(Parser, infixExpressionTest)
{

    struct InfixExpressionTestStruct
    {
        std::string expr;
        std::string op;
        int leftIntegerLiteral;
        int rightIntegerLiteral;
    };

    std::vector<InfixExpressionTestStruct> input = {{"10-5", "-", 10, 5}, {"1+5", "+", 1, 5}};

    for (auto const &ex : input)
    {

        std::shared_ptr<Lexer>
            lexer = std::make_shared<Lexer>(ex.expr);
        std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
        std::shared_ptr<Program> program = parser->parseProgram();

        EXPECT_NE(program, nullptr) << "Program is null.";
        EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";

        EXPECT_EQ(program->statements_.size(), 1) << "Program doesn't contain 1 statements as expected.";

        checkForParserErrors(parser);

        auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(program->statements_[0]);

        EXPECT_NE(expressionStatement, nullptr) << "Expected this statement to be a expression statement, is not.";

        auto infixOp = std::dynamic_pointer_cast<InfixExpression>(expressionStatement->Expr);

        EXPECT_NE(infixOp, nullptr) << "Expected this expression to be a an InfixExpression, is not.";

        EXPECT_TRUE(TestIntegerLiteral(infixOp->left, ex.leftIntegerLiteral)) << "TestIntegerLiteral FAIL\n";
        EXPECT_EQ(infixOp->op, ex.op) << "InfixExpression operator expected: " << ex.op << " , got: " << infixOp->op;
        EXPECT_TRUE(TestIntegerLiteral(infixOp->right, ex.rightIntegerLiteral))<<"TestIntegerLiteral FAIL\n";
    }
}

TEST(Parser, infixExpressionExtendedTest)
{

    struct InfixExpressionTestStruct
    {
        std::string input;
        std::string output;
    };

    std::vector<InfixExpressionTestStruct> input = {
        {"3 + 2 * 4", "(3 + (2 * 4))"},
        {
            "!-a",
            "(!(-a))",
        },
        {
            "a + b + c",
            "((a + b) + c)",
        },
        {
            "a + b - c",
            "((a + b) - c)",
        },
        {
            "a * b * c",
            "((a * b) * c)",
        },
        {
            "a * b / c",
            "((a * b) / c)",
        },
        {
            "a + b / c",
            "(a + (b / c))",
        },
        {
            "a + b * c + d / e - f",
            "(((a + (b * c)) + (d / e)) - f)",
        },
        {
            "3 + 4; -5 * 5",
            "(3 + 4)((-5) * 5)",
        },
        {
            "5 > 4 == 3 < 4",
            "((5 > 4) == (3 < 4))",
        },
        {
            "5 < 4 != 3 > 4",
            "((5 < 4) != (3 > 4))",
        },
        {
            "3 + 4 * 5 == 3 * 1 + 4 * 5",
            "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))",
        },
        {
            "3 + 4 * 5 == 3 * 1 + 4 * 5",
            "((3 + (4 * 5)) == ((3 * 1) + (4 * 5)))",
        }};

    for (auto const &ex : input)
    {

        std::shared_ptr<Lexer>
            lexer = std::make_shared<Lexer>(ex.input);
        std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
        std::shared_ptr<Program> program = parser->parseProgram();

        EXPECT_NE(program, nullptr) << "Program is null.";
        EXPECT_NE(program->statements_.empty(), true) << "Program has no statements.";

        checkForParserErrors(parser);

        auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(program->statements_[0]);

        EXPECT_NE(expressionStatement, nullptr) << "Expected this statement to be a expression statement, is not.";

        auto infixOpString = program->String();

        EXPECT_EQ(infixOpString, ex.output) << "Expected: " << ex.output << " , got: " << infixOpString;
    }
}

TEST(Parser, infixExpressionSimpleTests)
{

    struct InfixExpressionTestStruct
    {
        std::string expr;
        std::string op;
        int leftIntegerLiteral;
        int rightIntegerLiteral;
    };

    std::vector<InfixExpressionTestStruct> input = {{"10-5", "-", 10, 5}, {"1+5", "+", 1, 5}};

    for (auto const &ex : input)
    {

        std::shared_ptr<Lexer>
            lexer = std::make_shared<Lexer>(ex.expr);
        std::shared_ptr<Parser> parser = std::make_shared<Parser>(lexer);
        std::shared_ptr<Program> program = parser->parseProgram();

        auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(program->statements_[0]);
        EXPECT_NE(expressionStatement, nullptr) << "Expected this statement to be a expression statement, is not.";

        auto expression = std::dynamic_pointer_cast<Expression>(expressionStatement->Expr);
        EXPECT_NE(expression, nullptr) << "Expected this statement to be a expression, is not.";

        EXPECT_TRUE(testInfixExpression(expression, ex.leftIntegerLiteral, ex.op, ex.rightIntegerLiteral)) << "Fail";
    }
}