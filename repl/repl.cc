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
        std::shared_ptr<Parser> p = std::make_shared<Parser>(l);
        auto x = p->parseProgram();

        if(!(x->statements_.empty())){
            type_info(x->statements_[0]);
        }
        std::cout << x->String()<<std::endl;
        if(p->numberOfErrors() != 0){
            p->printErrors();
        }
    }
}

void Repl::type_info(std::shared_ptr<Statement> statement_)
{
    auto is_expression_statement = std::dynamic_pointer_cast<ExpressionStatement>(statement_);
    if (is_expression_statement)
    {
        auto is_expression = std::dynamic_pointer_cast<Expression>(is_expression_statement->Expr);
        if (is_expression)
            std::cout << "Type is:" << is_expression->Type() << std::endl;
        else
            std::cout << "Not a Expression" << std::endl;
    }
    else if (auto is_let_statement = std::dynamic_pointer_cast<LetStatement>(statement_))
    {
        std::cout << "Type is: LetStatement " << is_let_statement->name_->Type()
                  << " = " << std::dynamic_pointer_cast<Expression>(is_let_statement->value_)->Type() << std::endl;
    }

    else if (auto is_return_statement = std::dynamic_pointer_cast<ReturnStatement>(statement_))
    {
        std::cout << "Type is: ReturnStatement " << std::dynamic_pointer_cast<Expression>(is_return_statement->return_expression)->Type() 
                  << std::endl;
    }
    else
    {
        std::cout << "not a type" << std::endl;
    }
}