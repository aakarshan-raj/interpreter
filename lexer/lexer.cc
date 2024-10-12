#include "lexer.h"

void Lexer::read_char()
{
    if (next_position_ >= source_code_.length())
    {
        current_char_ = 0;
    }
    else
    {
        current_char_ = source_code_[next_position_];
    }
    current_position_ = next_position_;
    next_position_++;
}

Lexer::Lexer(std::string source_code) : source_code_(std::move(source_code))
{
    read_char();
}