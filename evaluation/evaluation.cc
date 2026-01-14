#include "evaluation.h"

std::shared_ptr<Object> Eval(std::shared_ptr<Node> node){
    auto expr_stat = std::dynamic_pointer_cast<ExpressionStatement>(node);
    if(auto inte_lit = std::dynamic_pointer_cast<IntegerLiteral>(expr_stat->Expr)){
        return std::make_shared<Integer>(inte_lit->value_);
    }
    return 0;
}