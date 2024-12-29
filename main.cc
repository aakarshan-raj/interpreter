#include "lexer/lexer.h"
#include <iostream>

int main()
{
    std::string source_code = R""""(let five = 5;
                                let ten = 10;
                                let add = fn(x, y) {
                                x + y;
                                };
                                let result = add(five, ten);)"""";
    Lexer l(source_code);

    for (auto x = l.next_token(); x.Type != EOF; x = l.next_token())
    {
        std::cout << x.Type << " " << x.Literal << std::endl;
    }
}