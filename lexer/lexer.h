#ifndef LEXER_H
#define LEXER_H
#include <iostream>

#include "../token/token.h"
class Lexer
{
private:
    std::string source_code_;
    int current_position_{0};
    int next_position_{0};
    char current_char_{0};
    void read_char();
    Token new_token(std::string, char);
    char peek();
    Token concate_single_token();

public:
    Lexer(std::string);
    Lexer() = default;
    ~Lexer() = default;
    Token next_token();
    bool isLetter(char);
    bool isDigit(char);
    std::string getWord();   // read till next char is not a letter
    std::string getDigit(); // read till next char is not a digit
    void skipWhiteSpace();
};

#endif