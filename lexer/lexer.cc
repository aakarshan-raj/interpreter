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

Token Lexer::new_token(std::string token_type, char token_literal)
{
    return Token{token_type, std::string{token_literal}};
}

Token Lexer::next_token()
{
    Token tok;
    switch (current_char_)
    {
    case '=':
        tok = new_token(ASSIGN, current_char_);
        break;
    case '+':
        tok = new_token(PLUS, current_char_);
        break;
    case ',':
        tok = new_token(COMMA, current_char_);
        break;
    case ';':
        tok = new_token(SEMICOLON, current_char_);
        break;
    case '(':
        tok = new_token(LPAREN, current_char_);
        break;
    case ')':
        tok = new_token(RPAREN, current_char_);
        break;
    case '{':
        tok = new_token(LBRACE, current_char_);
        break;
    case '}':
        tok = new_token(RBRACE, current_char_);
        break;
    case 0:
        tok.Literal = "";
        tok.Type = EOF;
        break;
    default:
        tok.Literal = "ILLEGAL";
        tok.Type = ILLEGAL;
        break;
    }
    read_char();
    return tok;
}

Lexer::Lexer(std::string source_code) : source_code_(std::move(source_code))
{
    read_char();
}