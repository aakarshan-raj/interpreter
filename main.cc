#include "lexer/lexer.h"
#include <iostream>

int main()
{
    std::string source_code = "((=))";
    Lexer l(source_code);

    for (int i = 0; i < source_code.length(); i++)
    {
        std::cout<<l.next_token().Literal<<std::endl;
    }
}