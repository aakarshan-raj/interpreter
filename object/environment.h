#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "object.h"
#include <unordered_map>
#include <optional>

class Environment
{
private:
    std::unordered_map<std::string, std::shared_ptr<Object>> store;

public:
    Environment();
    std::shared_ptr<Object> set(std::string,std::shared_ptr<Object>);
    std::optional<std::shared_ptr<Object>> get(std::string);
};

#endif