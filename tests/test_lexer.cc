#include <gtest/gtest.h>
#include "lexer.h"
#include <vector>
#include <string>

TEST(Lexer, SingleTokenTest)
{
    std::vector<Token> test_arr = {{ASSIGN, "="},
                                   {PLUS, "+"},
                                   {LPAREN, "("},
                                   {RPAREN, ")"},
                                   {LBRACE, "{"},
                                   {RBRACE, "}"},
                                   {COMMA, ","},
                                   {SEMICOLON, ";"},
                                   {EOF, ""}};
    std::string input = "=+(){},;";
    Lexer l(input);
    for (const auto &tok : test_arr)
    {
        Token result = l.next_token();
        EXPECT_EQ(tok.Type, result.Type) << "Expected:" << tok.Type << " Got:" << result.Type;
        EXPECT_EQ(tok.Literal, result.Literal) << "Expected:" << tok.Literal << " Got:" << result.Literal;
    }
    ASSERT_EQ(1, 1);
}