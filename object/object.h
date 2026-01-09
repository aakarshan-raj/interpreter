#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <iostream>

enum class ObjectType
{
    INTEGER,
    BOOLEAN,
    NOTHING,
};

class Object
{
public:
    virtual ObjectType Type();
    virtual std::string_view Inspect();
    virtual ~Object() = default;
};

class Integer : public Object
{
    int value;
    ObjectType Type() override;
    std::string_view Inspect() override;
};

class Boolean : public Object
{
    bool value;
    ObjectType Type() override;
    std::string_view Inspect() override;
};

class Null : public Object
{
    ObjectType Type() override;
    std::string_view Inspect() override;
};

#endif