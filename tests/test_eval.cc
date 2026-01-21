#include <gtest/gtest.h>
#include <vector>
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../object/object.h"
#include "../evaluation/evaluation.h"
#include <string>
#include <memory>

template <typename T>
struct InputOutput
{
    std::string input;
    T output;
};

template <typename T, typename U>
void TestObjects(std::shared_ptr<Object> obj, T expected)
{
    auto _obj = std::dynamic_pointer_cast<U>(obj);
    ASSERT_NE(_obj, nullptr) << "Object is not of expected type";
    EXPECT_EQ(_obj->value_, expected) << "Expected value to be:" << expected << " Is:" << _obj->value_;
}

std::shared_ptr<Object> TestEval(std::string &input)
{

    std::shared_ptr<Lexer> l = std::make_shared<Lexer>(input);
    std::shared_ptr<Parser> p = std::make_shared<Parser>(l);
    auto parsed_program = p->parseProgram();

    return Eval(parsed_program->statements_[0]);
}

void TestEvalIntegerExpression()
{
    std::vector<InputOutput<int>> tests = {{"5", 5}, {"10", 10}};
    for (auto &i : tests)
    {
        auto x = TestEval(i.input);
        TestObjects<int, Integer>(x, i.output);
    }
}

void TestEvalBooleanExpression()
{
    std::vector<InputOutput<bool>> tests = {{"true", true}, {"false", false}};
    for (auto &i : tests)
    {
        auto x = TestEval(i.input);
        TestObjects<bool, Boolean>(x, i.output);
    }
}

void TestBangOperatorEvaluation()
{
    std::vector<InputOutput<bool>> tests = {{"!true", false}, {"!false", true}};
    for (auto &i : tests)
    {
        auto x = TestEval(i.input);
        TestObjects<bool, Boolean>(x, i.output);
    }
}

TEST(Evaluation, TestEvalIntegerExpression)
{
    TestEvalIntegerExpression();
    TestEvalBooleanExpression();
    TestBangOperatorEvaluation();
}
