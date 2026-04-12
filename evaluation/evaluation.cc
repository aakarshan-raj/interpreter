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

std::shared_ptr<Boolean> EvalToNativeBoolean(bool EvalBool)
{
    if (EvalBool)
    {
        return native_true;
    }
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

std::shared_ptr<Object> EvalAdditionAdditionOperation(std::shared_ptr<Object> left, std::shared_ptr<Object> right)
{
    if (left->Type() != ObjectType::INTEGER && right->Type() != ObjectType::INTEGER)
        return nullptr;
    return std::make_shared<Integer>(
        std::dynamic_pointer_cast<Integer>(left)->value_ +
        std::dynamic_pointer_cast<Integer>(right)->value_);
}

std::shared_ptr<Object> EvalSubstractionOperation(std::shared_ptr<Object> left, std::shared_ptr<Object> right)
{
    if (left->Type() != ObjectType::INTEGER && right->Type() != ObjectType::INTEGER)
        return nullptr;
    return std::make_shared<Integer>(
        std::dynamic_pointer_cast<Integer>(left)->value_ -
        std::dynamic_pointer_cast<Integer>(right)->value_);
}
std::shared_ptr<Object> EvalMultiplicationOperation(std::shared_ptr<Object> left, std::shared_ptr<Object> right)
{
    if (left->Type() != ObjectType::INTEGER && right->Type() != ObjectType::INTEGER)
        return nullptr;
    return std::make_shared<Integer>(
        std::dynamic_pointer_cast<Integer>(left)->value_ *
        std::dynamic_pointer_cast<Integer>(right)->value_);
}
std::shared_ptr<Object> EvalDivisionOperation(std::shared_ptr<Object> left, std::shared_ptr<Object> right)
{
    if (left->Type() != ObjectType::INTEGER && right->Type() != ObjectType::INTEGER)
        return nullptr;
    return std::make_shared<Integer>(
        std::dynamic_pointer_cast<Integer>(left)->value_ /
        std::dynamic_pointer_cast<Integer>(right)->value_);
}

std::shared_ptr<Object> EvalEqualityOperation(std::shared_ptr<Object> left, std::shared_ptr<Object> right)
{
    if (left->Type() == ObjectType::INTEGER && right->Type() == ObjectType::INTEGER)
    {
        return EvalToNativeBoolean(
            std::dynamic_pointer_cast<Integer>(left)->value_ ==
            std::dynamic_pointer_cast<Integer>(right)->value_);
    }
    else if (left->Type() == ObjectType::BOOLEAN && right->Type() == ObjectType::BOOLEAN)
    {
        return EvalToNativeBoolean(left == right);
    }
}

std::shared_ptr<Object> EvalInEqualityOperation(std::shared_ptr<Object> left, std::shared_ptr<Object> right)
{
    if (left->Type() == ObjectType::INTEGER && right->Type() == ObjectType::INTEGER)
    {
        return EvalToNativeBoolean(
            std::dynamic_pointer_cast<Integer>(left)->value_ !=
            std::dynamic_pointer_cast<Integer>(right)->value_);
    }
    else if (left->Type() == ObjectType::BOOLEAN && right->Type() == ObjectType::BOOLEAN)
    {
        return EvalToNativeBoolean(left != right);
    }
}

std::shared_ptr<Object> EvalLessThanOperation(std::shared_ptr<Object> left, std::shared_ptr<Object> right)
{
    if (left->Type() != ObjectType::INTEGER && right->Type() != ObjectType::INTEGER)
        return nullptr;
    return EvalToNativeBoolean(
        std::dynamic_pointer_cast<Integer>(left)->value_ <
        std::dynamic_pointer_cast<Integer>(right)->value_);
}
std::shared_ptr<Object> EvalGreaterThanOperation(std::shared_ptr<Object> left, std::shared_ptr<Object> right)
{
    if (left->Type() != ObjectType::INTEGER && right->Type() != ObjectType::INTEGER)
        return nullptr;
    return EvalToNativeBoolean(
        std::dynamic_pointer_cast<Integer>(left)->value_ >
        std::dynamic_pointer_cast<Integer>(right)->value_);
}

std::shared_ptr<Object> EvalInfixExpression(std::shared_ptr<Object> left,
                                            std::string op,
                                            std::shared_ptr<Object> right) // opearations: + - / * == != < >
{
    if (op == "+")
    {
        return EvalAdditionAdditionOperation(left, right);
    }
    else if (op == "-")
    {
        return EvalSubstractionOperation(left, right);
    }
    else if (op == "/")
    {
        return EvalDivisionOperation(left, right);
    }
    else if (op == "*")
    {
        return EvalMultiplicationOperation(left, right);
    }
    else if (op == "==")
    {
        return EvalEqualityOperation(left, right);
    }
    else if (op == "!=")
    {
        return EvalInEqualityOperation(left, right);
    }
    else if (op == "<")
    {
        return EvalLessThanOperation(left, right);
    }
    else if (op == ">")
    {
        return EvalGreaterThanOperation(left, right);
    }
}

std::shared_ptr<Object> EvalStatement(std::vector<std::shared_ptr<Statement>> statements)
{
    std::shared_ptr<Object> statement_eval;
    for (auto single_statement : statements)
    {
        statement_eval = Eval(single_statement);
        if (auto return_val = std::dynamic_pointer_cast<ReturnValue>(statement_eval))
        {
            return return_val->value_;
        }
    }
    return statement_eval;
}

bool isTrue(std::shared_ptr<Object> condition_)
{
    if (auto expr_ = std::dynamic_pointer_cast<Null>(condition_))
    {
        return false;
    }
    else if (auto expr_ = std::dynamic_pointer_cast<Boolean>(condition_))
    {
        if (expr_->value_)
        {
            return true;
        }
        return false;
    }
    else
    {
        return true;
    }
}

std::shared_ptr<Object> EvalIfExpression(std::shared_ptr<IfExpression> ifExpression)
{
    auto condition_eval_ = Eval(ifExpression->condition_); // currenly it will be: a int, false, true, null
    if (isTrue(condition_eval_))
    {
        return Eval(ifExpression->consequence_);
    }
    else if (ifExpression != nullptr)
    {
        return Eval(ifExpression->alternative_);
    }
    else
    {
        return nullptr;
    }
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
    if (auto block_lit = std::dynamic_pointer_cast<BlockStatement>(node))
    {
        return EvalStatement(block_lit->statements);
    }
    if (auto cond_lit = std::dynamic_pointer_cast<IfExpression>(node))
    {
        return EvalIfExpression(cond_lit);
    }
    if (auto return_lit = std::dynamic_pointer_cast<ReturnStatement>(node))
    {
        auto val = Eval(return_lit->return_expression);
        return std::make_shared<ReturnValue>(val);
    }
    if (auto prefix_expr = std::dynamic_pointer_cast<PrefixExpression>(node))
    {
        auto prefix_obj = Eval(prefix_expr->right);
        return EvalPrefixExpression(prefix_expr->op, prefix_obj);
    }
    if (auto infix_expr = std::dynamic_pointer_cast<InfixExpression>(node))
    {
        auto left_evaluated = Eval(infix_expr->left);
        auto right_evaluated = Eval(infix_expr->right);
        return EvalInfixExpression(left_evaluated, infix_expr->op, right_evaluated);
    }

    return 0;
}
