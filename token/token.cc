#include "token.h"

std::map<std::string, std::string> lookUpTable{
    {"let", LET},
    {"fn", FUNCTION},
};


std::string lookUpToken(std::string tok)
{
    try
    {
        std::string look_tok = lookUpTable.at(tok);
        return look_tok;
    }
    catch (std::out_of_range &e)
    {
        return IDENT;
    }
}
