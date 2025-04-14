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

    return nullptr;
}

std::shared_ptr<Statement> Parser::parseStatement()
{
    if (current_token_.Type == LET)
    {
        auto stmt = praseLetStatement();
        return stmt;
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
    return false;
}
