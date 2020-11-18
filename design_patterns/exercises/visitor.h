#pragma once
#include <string>
#include <sstream>

namespace visitor
{
using namespace std;

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor
{
    // accept methods here :)
    virtual void accept(const Value& add) = 0;
    virtual void accept(const AdditionExpression& add) = 0;
    virtual void accept(const MultiplicationExpression& add) = 0;
};

struct Expression
{
    virtual void visit(ExpressionVisitor& ev) const = 0;
};

struct Value : Expression
{
    const int value;

    Value(const int value) : value(value) {}

    virtual void visit(ExpressionVisitor& ev) const
    {
        ev.accept(*this);
    }
};

struct AdditionExpression : Expression
{
    const Expression& lhs, & rhs;

    AdditionExpression(const Expression& lhs, const Expression& rhs) 
        : lhs(lhs), rhs(rhs) {}

    virtual void visit(ExpressionVisitor& ev) const
    {
        ev.accept(*this);
    }
};

struct MultiplicationExpression : Expression
{
    const Expression& lhs, & rhs;

    MultiplicationExpression(const Expression& lhs, const Expression& rhs)
        : lhs(lhs), rhs(rhs) {}

    virtual void visit(ExpressionVisitor& ev) const
    {
        ev.accept(*this);
    }
};

struct ExpressionPrinter : ExpressionVisitor
{
    // accept methods here :)

    ostringstream oss;

    string str() const { return oss.str(); }

    virtual void accept(const Value& add)
    {
        oss << add.value;
    }

    virtual void accept(const AdditionExpression& add)
    {
        oss << "(";
        add.lhs.visit(*this); 
        oss << "+";
        add.rhs.visit(*this);   
        oss << ")";
    }
    virtual void accept(const MultiplicationExpression& add)
    {
        add.lhs.visit(*this);
        oss << "*";
        add.rhs.visit(*this);   
    }
};
}