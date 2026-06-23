#include "environment.h"
#include "object.h"

Environment::Environment() {}

std::shared_ptr<Object> Environment::set(std::string var, std::shared_ptr<Object> value)
{
    store[var] = value;
    return value;
}

std::optional<std::shared_ptr<Object>> Environment::get(std::string var_name)
{
    auto it = store.find(var_name);
    if (it == store.end() && outer != nullptr)
    {
        return outer->get(var_name);
    }
    else if (it == store.end() && outer == nullptr)
    {
        return std::nullopt;
    }
    return it->second;
}

std::shared_ptr<Environment> Environment::newEnclosedEnvironment(std::shared_ptr<Environment> outer_env)
{
    std::shared_ptr<Environment> env = std::make_shared<Environment>();
    env->outer = outer_env;
    return env;
}