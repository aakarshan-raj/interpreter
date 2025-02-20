#include "parser.h"

void Parser::NextToken()
{
    current_token_ = peek_token_;
    peek_token_ = lexer_->next_token();
}

std::shared_ptr<Program> Parser::ParseProgram()
{
  std::shared_ptr<Program> program = std::make_shared<Program>();
    while (current_token_.Type != EOF)
    {
        std::shared_ptr<Statement> stmt = ParseStatement();
        if (stmt != nullptr)
        {   
            program->statements_.push_back(stmt);
        }
        NextToken();
    }

    return nullptr;
}