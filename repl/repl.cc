#include "repl.h"

void Repl::start()
{

    while (true)
    {
        std::cout << ">> ";
        std::getline(std::cin, input_);
        if (input_ == "exit")
            break;
        std::shared_ptr<Lexer> l = std::make_shared<Lexer>(input_);
        // for (auto x = l->next_token(); x.Type != EOF; x = l->next_token())
        // {
        //     std::cout << x;
        // }
        std::shared_ptr<Parser> p = std::make_shared<Parser>(l);
        auto x = p->parseProgram();
        for (const auto &y : x->statements_)
        {
            std::cout << y->TokenLiteral();
        }
    }
}
