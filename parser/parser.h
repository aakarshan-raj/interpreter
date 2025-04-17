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
    std::vector<std::string> logErrors();


private:
    std::shared_ptr<Lexer> lexer_;
    Token current_token_;
    Token peek_token_;
    void nextToken();

    // CORE
    std::shared_ptr<Statement> parseStatement();
    std::shared_ptr<Statement> praseLetStatement();
    std::shared_ptr<Statement> parseReturnStatement();

    bool currentTokenIs(const std::string &);
    bool peekTokenIs(const std::string &);
    bool expectToken(const std::string &);

    std::vector<std::string> errors;


    void peekError(const std::string&);
};

#endif