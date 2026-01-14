#ifndef EVALUATION_H
#define EVALUATION_H
#include "../object/object.h"
#include <memory>
#include "../ast/ast.h"

std::shared_ptr<Object> Eval(std::shared_ptr<Node>);

#endif