#include <string>
#include <iostream>

class node{

    public:
        virtual std::string TokenLiteral() const = 0;
        virtual ~node () = default;

};

class statement: public node{
    void statement_node();

};

class expression: public node{
    void expression_node();

};





