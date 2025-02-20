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
        this->NextToken();
        this->NextToken();
    }
    std::shared_ptr<Program> ParseProgram();

private:
    std::shared_ptr<Lexer> lexer_;
    Token current_token_;
    Token peek_token_;
    void NextToken();
    std::shared_ptr<Statement> ParseStatement();    
};

#endif