#include "parser.h"

void Parser::nextToken()
{
    current_token_ = peek_token_;
    peek_token_ = lexer_->next_token();
}

std::shared_ptr<Program> Parser::parseProgram()
{
    std::shared_ptr<Program> program = std::make_shared<Program>();
    while (current_token_.Type != EOF)
    {
        std::shared_ptr<Statement> stmt = parseStatement();
        if (stmt != nullptr)
        {
            program->statements_.push_back(stmt);
        }
        nextToken();
    }
    return program;
}

std::shared_ptr<Statement> Parser::parseStatement()
{
    if (current_token_.Type == LET)
    {
        auto letStmt = praseLetStatement();
        return letStmt;
    }
    else if (current_token_.Type == RETURN){
        auto returnStmt = parseReturnStatement();
        return returnStmt;
    }
    else
    {
        return nullptr;
    }
}

std::shared_ptr<Statement> Parser::praseLetStatement()
{
    auto letStatement = std::make_shared<LetStatement>(current_token_);
    if (!expectToken(IDENT))
    {
        return nullptr;
    }

    letStatement->name_ = std::make_shared<Identifier>(current_token_);

    if (!expectToken(ASSIGN))
    {
        return nullptr;
    }

    while (!currentTokenIs(SEMICOLON))
    {
        nextToken();
    }
    return letStatement;
}

bool Parser::currentTokenIs(const std::string &token)
{
    if (current_token_.Type == token)
    {
        return true;
    }
    return false;
}

bool Parser::peekTokenIs(const std::string &token)
{
    if (peek_token_.Type == token)
    {
        return true;
    }
    return false;
}

bool Parser::expectToken(const std::string &token)
{
    if (peekTokenIs(token))
    {
        nextToken();
        return true;
    }
    peekError(token);
    return false;
}

std::vector<std::string> Parser::logErrors()
{
    return errors;
}

void Parser::peekError(const std::string &t)
{
    std::string error_message = "Expected : " + t + ", Got : " + peek_token_.Type;
    errors.push_back(error_message);
}

std::shared_ptr<Statement> Parser::parseReturnStatement(){
    auto stmt = std::make_shared<ReturnStatement>(current_token_);

    nextToken();

    if(!expectToken(SEMICOLON)){
        nextToken();
    }
    return stmt;
}

