#include <gtest/gtest.h>
#include <vector>
#include "../parser/parser.h"
#include "../lexer/lexer.h"
#include "../object/object.h"
#include "../evaluation/evaluation.h"
#include <string>
#include <memory>

struct IntInputOutput
{
    std::string input;
    int output;
};

std::shared_ptr<Object> TestEval(std::string &input)
{

    std::shared_ptr<Lexer> l = std::make_shared<Lexer>(input);
    std::shared_ptr<Parser> p = std::make_shared<Parser>(l);
    auto parsed_program = p->parseProgram();

    return Eval(parsed_program->statements_[0]);
}

void TestIntegerObject(std::shared_ptr<Object> obj, int expected)
{
    auto inte_obj = std::dynamic_pointer_cast<Integer>(obj);
    ASSERT_NE(inte_obj, nullptr) << "Object is not an Integer";
    EXPECT_EQ(inte_obj->value_, expected) << "Expected value to be:" << expected << " Is:" << inte_obj->value_;
}

void TestEvalIntegerExpression()
{
    std::vector<IntInputOutput> tests = {{"5", 5}, {"10", 10}};
    for (auto &i : tests)
    {
        auto x = TestEval(i.input);
        TestIntegerObject(x, i.output);
    }
}

TEST(Evaluation, TestEvalIntegerExpression)
{
    TestEvalIntegerExpression();
}
