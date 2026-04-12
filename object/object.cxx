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

ObjectType ReturnValue::Type() const
{
    return ObjectType::RETURN_VALUE;
}

std::string_view ReturnValue::Inspect() const
{
    return value_->Inspect();
}

std::ostream& operator<<(std::ostream& os, ObjectType type)
{
    switch (type)
    {
        case ObjectType::INTEGER:
            os << "INTEGER";
            break;
        case ObjectType::BOOLEAN:
            os << "BOOLEAN";
            break;
        case ObjectType::NOTHING:
            os << "NOTHING";
            break;
        case ObjectType::RETURN_VALUE:
            os << "RETURN_VALUE";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}
