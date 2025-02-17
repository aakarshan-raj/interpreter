#include "parser.h"

void Parser::NextToken()
{
    current_token_ = peek_token_;
    peek_token_ = lexer_->next_token();
}

std::shared_ptr<Program> Parser::ParseProgram()
{
    return nullptr;
}