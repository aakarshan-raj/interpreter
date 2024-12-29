#include <gtest/gtest.h>
#include "lexer.h"
#include <vector>
#include <string>

TEST(Lexer, SingleCharTokenTest)
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
}

TEST(Lexer, isLetter)
{
    struct TestStructIsLetter
    {
        char ch;
        bool result;
    };
    Lexer lex("test");
    std::vector<TestStructIsLetter> test_arr = {{'a', true}, {'b', true}, {'+', false}, {'$', false}};
    for (const auto &ch : test_arr)
    {
        EXPECT_EQ(ch.result, lex.isLetter(ch.ch)) << "Expected:" << ch.result << " Got:" << lex.isLetter(ch.ch) << ". For" << ch.ch;
    }
}

TEST(Lexer, isDigit)
{
    struct TestStructIsDigit
    {
        char ch;
        bool result;
    };
    Lexer lex("test");
    std::vector<TestStructIsDigit> test_arr = {{'9', true}, {'2', true}, {'a', false}, {'z', false}};
    for (const auto &ch : test_arr)
    {
        EXPECT_EQ(ch.result, lex.isDigit(ch.ch)) << "Expected:" << ch.result << " Got:" << lex.isDigit(ch.ch) << ". For" << ch.ch;
    }
}

TEST(Lexer, MultiCharTokenTest)
{
    std::vector<Token> test_arr = {{LET, "let"},
                                   {IDENT, "five"},
                                   {ASSIGN, "="},
                                   {INT, "5"},
                                   {SEMICOLON, ";"},
                                   {LET, "let"},
                                   {IDENT, "ten"},
                                   {ASSIGN, "="},
                                   {INT, "10"},
                                   {SEMICOLON, ";"},
                                   {LET, "let"},
                                   {IDENT, "add"},
                                   {ASSIGN, "="},
                                   {FUNCTION, "fn"},
                                   {LPAREN, "("},
                                   {IDENT, "x"},
                                   {COMMA, ","},
                                   {IDENT, "y"},
                                   {RPAREN, ")"},
                                   {LBRACE, "{"},
                                   {IDENT, "x"},
                                   {PLUS, "+"},
                                   {IDENT, "y"},
                                   {SEMICOLON, ";"},
                                   {RBRACE, "}"},
                                   {SEMICOLON, ";"},
                                   {LET, "let"},
                                   {IDENT, "result"},
                                   {ASSIGN, "="},
                                   {IDENT, "add"},
                                   {LPAREN, "("},
                                   {IDENT, "five"},
                                   {COMMA, ","},
                                   {IDENT, "ten"},
                                   {RPAREN, ")"},
                                   {SEMICOLON, ";"},
                                   {EOF, ""}};
    std::string input = R""""(let five = 5;
                                let ten = 10;
                                let add = fn(x, y) {
                                x + y;
                                };
                                let result = add(five, ten);)"""";
    Lexer l(input);
    for (const auto &tok : test_arr)
    {

        Token result = l.next_token();
        EXPECT_EQ(tok.Type, result.Type) << "Expected:" << tok.Type << '\n'
                                         << "     Got:" << result.Type;
        EXPECT_EQ(tok.Literal, result.Literal) << "Expected:" << tok.Literal << '\n'
                                               << "     Got:" << result.Literal;
    }
}

TEST(Lexer, NewTokensTest)
{
    std::vector<Token> test_arr = {{LET, "let"},
                                   {IDENT, "five"},
                                   {ASSIGN, "="},
                                   {INT, "5"},
                                   {SEMICOLON, ";"},
                                   {LET, "let"},
                                   {IDENT, "ten"},
                                   {ASSIGN, "="},
                                   {INT, "10"},
                                   {SEMICOLON, ";"},
                                   {LET, "let"},
                                   {IDENT, "add"},
                                   {ASSIGN, "="},
                                   {FUNCTION, "fn"},
                                   {LPAREN, "("},
                                   {IDENT, "x"},
                                   {COMMA, ","},
                                   {IDENT, "y"},
                                   {RPAREN, ")"},
                                   {LBRACE, "{"},
                                   {IDENT, "x"},
                                   {PLUS, "+"},
                                   {IDENT, "y"},
                                   {SEMICOLON, ";"},
                                   {RBRACE, "}"},
                                   {SEMICOLON, ";"},
                                   {LET, "let"},
                                   {IDENT, "result"},
                                   {ASSIGN, "="},
                                   {IDENT, "add"},
                                   {LPAREN, "("},
                                   {IDENT, "five"},
                                   {COMMA, ","},
                                   {IDENT, "ten"},
                                   {RPAREN, ")"},
                                   {SEMICOLON, ";"},
                                   {BANG, "!"},
                                   {MINUS, "-"},
                                   {SLASH, "/"},
                                   {ASTERISK, "*"},
                                   {INT, "5"},
                                   {SEMICOLON, ";"},
                                   {INT, "5"},
                                   {LT, "<"},
                                   {INT, "10"},
                                   {GT, ">"},
                                   {INT, "5"},
                                   {SEMICOLON, ";"},

                                   {IF, "if"},
                                   {LPAREN, "("},
                                   {INT, "5"},
                                   {LT, "<"},
                                   {INT, "10"},
                                   {RPAREN, ")"},
                                   {LBRACE, "{"},
                                   {RETURN, "return"},
                                   {TRUE, "true"},
                                   {SEMICOLON, ";"},
                                   {RBRACE, "}"},
                                   {ELSE, "else"},
                                   {LBRACE, "{"},
                                   {RETURN, "return"},
                                   {FALSE, "false"},
                                   {SEMICOLON, ";"},
                                   {RBRACE, "}"},

                                   {INT, "10"},
                                   {EQUALITY, "=="},
                                   {INT, "10"},
                                   {SEMICOLON, ";"},
                                   {INT, "10"},
                                   {INEQUALITY, "!="},
                                   {INT, "9"},
                                   {SEMICOLON, ";"},

                                   {EOF, ""}};

    std::string input = R""""(let five = 5;
                        let ten = 10;
                        let add = fn(x, y) {
                            x + y;
                        };
                        let result = add(five, ten);
                        !-/*5;
                        5 < 10 > 5;
                     
                        if (5 < 10) {
                           return true;
                        } else {
                            return false;
                        }

                        10 == 10;
                        10 != 9;
                        
                        )"""";
    Lexer l(input);
    for (const auto &tok : test_arr)
    {

        Token result = l.next_token();
        EXPECT_EQ(tok.Type, result.Type) << "Expected:" << tok.Type << '\n'
                                         << "     Got:" << result.Type;
        EXPECT_EQ(tok.Literal, result.Literal) << "Expected:" << tok.Literal << '\n'
                                               << "     Got:" << result.Literal;
    }
}
