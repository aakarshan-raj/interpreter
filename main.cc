#include "lexer/lexer.h"
#include <iostream>

int main()
{
    std::string source_code = "((ab= 933+)";
    Lexer l(source_code);

    for (auto x = l.next_token(); x.Type != EOF; x = l.next_token())
    {
        std::cout << x.Type << std::endl;
    }
}