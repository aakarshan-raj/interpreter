#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"
class Lexer
{
private:
    std::string source_code_;
    int current_position_{0};
    int next_position_{0};

    Token new_token(std::string, char);

public:
    Lexer(std::string);
    ~Lexer() = default;
    Token next_token();
    char current_char_{0};
    void read_char();
};

#endif