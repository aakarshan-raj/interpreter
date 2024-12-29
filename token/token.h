#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>
#include <stdexcept>

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

#define MINUS "-"
#define BANG "!"
#define ASTERISK "*"
#define SLASH "/"
#define LT "<"
#define GT ">"

#define IF "IF"
#define ELSE "*"

#define RETURN "return"
#define TRUE "true"
#define FALSE "false"

#define EQUALITY "=="
#define INEQUALITY "!="

struct Token
{
    std::string Type;
    std::string Literal;
};

std::string lookUpToken(std::string tok);

#endif