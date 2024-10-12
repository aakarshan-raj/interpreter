#include "lexer/lexer.h"
#include <iostream>

int main()
{
    std::string source_code = "a b c e d";
    Lexer l(source_code);

    for (int i = 0; i < source_code.length(); i++)
    {
        std::cout<<l.current_char_<<std::endl;
        l.read_char();
    }
}