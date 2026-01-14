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
public:
    explicit Integer(int value):value_(value){};
    int value_;
    ObjectType Type() const override;
    std::string_view Inspect() const override;
};

class Boolean : public Object
{
public:
    explicit Boolean(int value):value_(value){};
    bool value_;
    ObjectType Type() const override;
    std::string_view Inspect() const override;
};

class Null : public Object
{
public:
    ObjectType Type() const override;
    std::string_view Inspect() const override;
};

#endif