#include "object.h"

ObjectType Integer::Type() const
{
    return ObjectType::INTEGER;
}

std::string_view Integer::Inspect() const
{
    std::cout << value_ << std::endl;
}

ObjectType Boolean::Type() const
{
    return ObjectType::BOOLEAN;
}

std::string_view Boolean::Inspect() const
{
    std::cout << value_ << std::endl;
}

ObjectType Null::Type() const
{
    return ObjectType::NOTHING;
}

std::string_view Null::Inspect() const
{
    std::cout << "null" << std::endl;
}