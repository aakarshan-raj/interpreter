#include "object.h"

ObjectType Integer::Type()
{
    return ObjectType::INTEGER;
}

std::string_view Integer::Inspect()
{
    std::cout<<value<<std::endl;
}

ObjectType Boolean::Type()
{
    return ObjectType::BOOLEAN;
}

std::string_view Boolean::Inspect()
{
    std::cout<<value<<std::endl;

}

ObjectType Null::Type()
{
    return ObjectType::NOTHING;
}

std::string_view Null::Inspect()
{
    std::cout<<"null"<<std::endl;
}