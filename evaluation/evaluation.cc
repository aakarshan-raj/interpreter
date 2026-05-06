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
    {
        std::ostringstream oss;
        oss << "unknown operator: -" << right->Type();

        return std::make_shared<Error>(oss.str());
    }
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
    {
        std::ostringstream oss;
        oss << "unknown operator: " << left->Type() << " + " << right->Type();

        return std::make_shared<Error>(oss.str());
    }

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
    if (left->Type() != right->Type())
    {
        std::ostringstream oss;
        oss << "type mismatch: " << left->Type() << " + " << right->Type();

        return std::make_shared<Error>(oss.str());
    }
    else if (op == "+")
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
    else
    {
        return std::make_shared<Error>("Unknown operator");
    }
}

std::shared_ptr<Object> EvalStatement(std::vector<std::shared_ptr<Statement>> statements, std::shared_ptr<Environment> env)
{
    std::shared_ptr<Object> statement_eval;
    for (auto single_statement : statements)
    {
        statement_eval = Eval(single_statement, env);
        if (auto error_val = std::dynamic_pointer_cast<Error>(statement_eval))
        {
            return error_val;
        }
        if (auto return_val = std::dynamic_pointer_cast<ReturnValue>(statement_eval))
        {
            return return_val;
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

bool isError(std::shared_ptr<Object> object_in_question)
{
    if (object_in_question->Type() == ObjectType::ERROR)
    {
        return true;
    }
    return false;
}

std::shared_ptr<Object> EvalIfExpression(std::shared_ptr<IfExpression> ifExpression, std::shared_ptr<Environment> env)
{
    auto condition_eval_ = Eval(ifExpression->condition_, env); // currenly it will be: a int, false, true, null
    if (isError(condition_eval_))
    {
        return condition_eval_;
    }
    if (isTrue(condition_eval_))
    {
        return Eval(ifExpression->consequence_, env);
    }
    else if (ifExpression->alternative_ != nullptr)
    {
        return Eval(ifExpression->alternative_, env);
    }
    else
    {
        return nullptr;
    }
}

std::shared_ptr<Object> EvalIdentifier(std::shared_ptr<Identifier> Identifier, std::shared_ptr<Environment> env)
{
    if (env->get(Identifier->value_).has_value())
    {
        return env->get(Identifier->value_).value();
    }
    else
    {
        std::ostringstream oss;
        oss << "identifier not found: " << Identifier->value_;
        return std::make_shared<Error>(oss.str());
    }
}

std::shared_ptr<Object> Eval(std::shared_ptr<Node> node, std::shared_ptr<Environment> env)
{
    if (auto expr_stat = std::dynamic_pointer_cast<ExpressionStatement>(node))
    {
        return Eval(expr_stat->Expr, env);
    }
    if (auto program = std::dynamic_pointer_cast<Program>(node))
    {
        return EvalStatement(program->statements_, env);
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
        return EvalStatement(block_lit->statements, env);
    }
    if (auto cond_lit = std::dynamic_pointer_cast<IfExpression>(node))
    {
        return EvalIfExpression(cond_lit, env);
    }
    if (auto return_lit = std::dynamic_pointer_cast<ReturnStatement>(node))
    {
        std::shared_ptr<Object> val = Eval(return_lit->return_expression, env);
        if (isError(val))
        {
            return val;
        }
        return std::make_shared<ReturnValue>(val);
    }
    if (auto prefix_expr = std::dynamic_pointer_cast<PrefixExpression>(node))
    {
        auto prefix_obj = Eval(prefix_expr->right, env);
        if (isError(prefix_obj))
        {
            return prefix_obj;
        }
        return EvalPrefixExpression(prefix_expr->op, prefix_obj);
    }
    if (auto infix_expr = std::dynamic_pointer_cast<InfixExpression>(node))
    {
        auto left_evaluated = Eval(infix_expr->left, env);
        if (isError(left_evaluated))
        {
            return left_evaluated;
        }
        auto right_evaluated = Eval(infix_expr->right, env);
        if (isError(right_evaluated))
        {
            return right_evaluated;
        }
        return EvalInfixExpression(left_evaluated, infix_expr->op, right_evaluated);
    }
    if (auto let_stat = std::dynamic_pointer_cast<LetStatement>(node))
    {
        auto eval_value_ = Eval(let_stat->value_, env);
        if (isError(eval_value_))
        {
            return eval_value_;
        }
        env->set(let_stat->name_->value_, eval_value_);
    }
    if (auto iden = std::dynamic_pointer_cast<Identifier>(node))
    {
        return EvalIdentifier(iden, env);
    }

    return 0;
}
