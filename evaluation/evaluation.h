#ifndef EVALUATION_H
#define EVALUATION_H
#include "../object/object.h"
#include <memory>
#include "../ast/ast.h"

std::shared_ptr<Object> Eval(std::shared_ptr<Node>);

inline const auto native_true = std::make_shared<Boolean>(true);
inline const auto native_false = std::make_shared<Boolean>(false);
inline const auto native_null = std::make_shared<Null>();

#endif