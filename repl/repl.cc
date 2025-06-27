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

        type_info(x->statements_[0]);
        std::cout << x->String();
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
        // Expression part of let is not yet parsed with let statement
        std::cout << "Type is: LetStatement " << is_let_statement->name_->Type()
                  << " = " << "NOT_YET_PARSED_WITH_THIS_STATEMENT" << std::endl;
    }

    else if (auto is_return_statement = std::dynamic_pointer_cast<ReturnStatement>(statement_))
    {
        // Expression part of let is not yet parsed with return statement
        std::cout << "Type is: ReturnStatement " << "NOT_YET_PARSED_WITH_THIS_STATEMENT"
                  << std::endl;
    }
    else
    {
        std::cout << "not a type" << std::endl;
    }
}