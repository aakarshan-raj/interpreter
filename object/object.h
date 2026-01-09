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
    virtual ObjectType Type() const = 0;
    virtual std::string_view Inspect() const = 0;
    virtual ~Object() = default;
};

class Integer : public Object
{
    int value;
    ObjectType Type() const override;
    std::string_view Inspect() const override;
};

class Boolean : public Object
{
    bool value;
    ObjectType Type() const override;
    std::string_view Inspect() const override;
};

class Null : public Object
{
    ObjectType Type() const override;
    std::string_view Inspect() const override;
};

#endif