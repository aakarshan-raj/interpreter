#include "../lexer/lexer.h"
#include <iostream>

class Repl
{
private:
    std::string input_;
    char repl_char_;

public:
    void start();
};
