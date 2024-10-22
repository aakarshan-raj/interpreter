#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#define ASSIGN "ASSIGN"
#define ILLEGAL "ILLEGAL"
#define EOF "EOF"
#define IDENT "IDENT"
#define INT "INT"
#define ASSIGN "ASSIGN"
#define PLUS "PLUS"
#define COMMA "COMMA"
#define SEMICOLON "SEMICOLON"
#define LPAREN "LPAREN"
#define RPAREN "RPAREN"
#define LBRACE "LBRACE"
#define RBRACE "RBRACE"
#define FUNCTION "FUNCTION"
#define LET "LET"

struct Token
{
    std::string Type;
    std::string Literal;
};

#endif