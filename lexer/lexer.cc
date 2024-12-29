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
    skipWhiteSpace();
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
        if (isLetter(current_char_))
        {
            std::string word = getWord();
            std::string word_type = lookUpToken(word);
            tok.Literal = word;
            tok.Type = word_type;
        }
        else if (isDigit(current_char_))
        {
            std::string digit = getDigit();
            tok.Literal = digit;
            tok.Type = INT;
        }
        else
        {
            tok.Literal = current_char_;
            tok.Type = ILLEGAL;
        }

        break;
    }
    read_char();
    return tok;
}

Lexer::Lexer(std::string source_code) : source_code_(std::move(source_code))
{
    read_char();
}

bool Lexer::isLetter(char ch)
{
    if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z' || ch == '_')
    {
        return true;
    }
    return false;
}

bool Lexer::isDigit(char ch)
{
    if (ch >= '0' && ch <= '9' || ch == '.')
    {
        return true;
    }
    return false;
}

void Lexer::skipWhiteSpace()
{
    while (current_char_ == ' ' || current_char_ == '\n' || current_char_ == '\t' || current_char_ == '\r')
    {
        read_char();
    }
}

std::string Lexer::getWord()
{
    std::string word;
    word.push_back(current_char_);
    while (isLetter(source_code_[next_position_]) && next_position_ < source_code_.length())
    {
        read_char();
        word.push_back(current_char_);
    }
    return word;
}

std::string Lexer::getDigit()
{
    std::string word;
    word.push_back(current_char_);
    while (isDigit(source_code_[next_position_]) && next_position_ < source_code_.length())
    {
        read_char();
        word.push_back(current_char_);
    }
    return word;
}