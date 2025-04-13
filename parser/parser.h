#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include "../token/token.h"
#include <memory>
#include "../lexer/lexer.h"
#include "../ast/ast.h"
class Parser
{
public:
    Parser(std::shared_ptr<Lexer> lexer) : lexer_{lexer}
    {
        this->nextToken();
        this->nextToken();
    }
    std::shared_ptr<Program> parseProgram();

private:
    std::shared_ptr<Lexer> lexer_;
    Token current_token_;
    Token peek_token_;
    void nextToken();
    std::shared_ptr<Statement> parseStatement();
    std::shared_ptr<Statement> Parser::praseLetStatement();

    bool currentTokenIs(std::string &);
    bool Parser::peekTokenIs(std::string &);
    bool expectToken(std::string&);
};

#endif