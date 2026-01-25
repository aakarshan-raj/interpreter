#include "repl/repl.h"
#include <iostream>

int main(int args, char **argc)
{
    bool PRINT_DEBUG_INFO = false;
    if (args > 1)
    {

        if (std::string(argc[1]) == "debug")
        {
            PRINT_DEBUG_INFO = true;
        }
    }

    Repl r1{};
    r1.start(PRINT_DEBUG_INFO);

    return 0;
}
