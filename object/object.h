#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <iostream>
#include <memory>

enum class ObjectType
{
    INTEGER,
    BOOLEAN,
    NOTHING,
    RETURN_VALUE
};

std::ostream& operator<<(std::ostream& os, ObjectType type);

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
    explicit Integer(int value) : value_(value) {};
    int value_;
    ObjectType Type() const override;
    std::string_view Inspect() const override;
};

class Boolean : public Object
{
public:
    explicit Boolean(bool value) : value_(value) {};
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

class ReturnValue : public Object
{
public:
    explicit ReturnValue(std::shared_ptr<Object> value) : value_(value) {};
    std::shared_ptr<Object> value_;
    ObjectType Type() const override;
    std::string_view Inspect() const override;
};

#endif