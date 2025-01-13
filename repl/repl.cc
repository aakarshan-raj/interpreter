#include "repl.h"

void Repl::start()
{

    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, input_);
        if (input_ == "exit")
            break;
        Lexer l(input_);

        for (auto x = l.next_token(); x.Type != EOF; x = l.next_token())
        {
            std::cout << x;
        }
    }
}
