#include "evaluation.h"

std::shared_ptr<Object> EvalBangOperatorExpression(std::shared_ptr<Object> right)
{
    if (right == native_true)
        return native_false;
    if (right == native_false)
        return native_true;
    if (right == native_null)
        return native_true;
    return native_false;
}

std::shared_ptr<Object> EvalMinusOperatorExpression(std::shared_ptr<Object> right)
{
    if (right->Type() != ObjectType::INTEGER)
        return nullptr;
    return std::make_shared<Integer>(-std::dynamic_pointer_cast<Integer>(right)->value_);
}

std::shared_ptr<Object> EvalPrefixExpression(std::string op, std::shared_ptr<Object> right)
{
    if (op == "!")
    {
        return EvalBangOperatorExpression(right);
    }
    else if (op == "-")
    {
        return EvalMinusOperatorExpression(right);
    }
    else
    {
        return nullptr;
    }
}

std::shared_ptr<Object> EvalStatement(std::vector<std::shared_ptr<Statement>> statements)
{
    std::shared_ptr<Object> statement_eval;
    for (auto single_statement : statements)
    {
        statement_eval = Eval(single_statement);
    }
    return statement_eval;
}

std::shared_ptr<Object> Eval(std::shared_ptr<Node> node)
{
    if (auto expr_stat = std::dynamic_pointer_cast<ExpressionStatement>(node))
    {
        return Eval(expr_stat->Expr);
    }
    if (auto program = std::dynamic_pointer_cast<Program>(node))
    {
        return EvalStatement(program->statements_);
    }
    if (auto inte_lit = std::dynamic_pointer_cast<IntegerLiteral>(node))
    {
        return std::make_shared<Integer>(inte_lit->value_);
    }
    if (auto bool_lit = std::dynamic_pointer_cast<BooleanLiteral>(node))
    {
        if (bool_lit->value_)
        {
            return native_true;
        }
        return native_false;
    }
    if (auto prefix_expr = std::dynamic_pointer_cast<PrefixExpression>(node))
    {
        auto prefix_obj = Eval(prefix_expr->right);
        return EvalPrefixExpression(prefix_expr->op, prefix_obj);
    }

    return 0;
}
