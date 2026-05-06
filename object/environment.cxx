#include "environment.h"

Environment::Environment() {}

std::shared_ptr<Object> Environment::set(std::string var, std::shared_ptr<Object> value)
{
    store[var] = value;
    return value;
}

std::optional<std::shared_ptr<Object>> Environment::get(std::string var_name)
{
    auto it = store.find(var_name);
    if (it != store.end())
    {
        return it->second;
    }
    return std::nullopt;
}
