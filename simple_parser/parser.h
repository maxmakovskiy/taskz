#pragma once
#include <memory>
#include <stack>

class Node
{
public:
    virtual int Evaluate() const = 0;
};

class Value : public Node
{
public:
    Value(char digit)
        : value(digit - '0')
    {}
    
    int Evaluate() const override
    {
        return value;
    }

private:
    const int value; 
};

class Variable : public Node
{
public:
    Variable(const int& x)
        : x(x)
    {}

    int Evaluate() const override
    {
        return x;
    }

private:
    const int& x;

};

class Operation : public Node
{
public:
    const int priority;

    Operation(char value)
        : priority([value] {
                    return value == '*' ? 2 : 1;
                }())
        , op(value)
    {}

    int Evaluate() const override
    {
        if (op == '*') {
            return left->Evaluate() * right->Evaluate();
        } else if (op == '+') {
            return left->Evaluate() + right->Evaluate();
        } else if (op == '-') {
            return left->Evaluate() - right->Evaluate();
        }
    
        return 0;
    }
    
    void SetLeft(std::shared_ptr<Node> node)
    {
        left = node;
    }

    void SetRight(std::shared_ptr<Node> node)
    {
        right = node;
    }

private:
    const char op;
    std::shared_ptr<const Node> left, right;
};

// Shunting yard algorithm
template <typename It>
std::shared_ptr<Node> Parse(It begin, It end, const int& x)
{
    if (begin == end) return std::make_shared<Value>('0');

    std::stack<std::shared_ptr<Node>> values;
    std::stack<std::shared_ptr<Operation>> ops;

    auto PopupOperations = [&](int priority) {
        while (!ops.empty() && (ops.top()->priority >= priority))
        {
            auto v1 = values.top();
            values.pop();
            auto v2 = values.top();
            values.pop();
            auto op = ops.top();
            ops.pop();

            op->SetRight(v1);
            op->SetLeft(v2);

            values.push(op);
        }
    };

    while (begin != end)
    {
        const auto& value = *begin;

        if (value >= '0' && value <= '9') {
            values.push(std::make_shared<Value>(value));
        } else if (value == 'x') {
            values.push(std::make_shared<Variable>(x));
        } else if (value == '*') {
            PopupOperations(2);
            ops.push(std::make_shared<Operation>(value));
        } else if (value == '+' || value == '-') {
            PopupOperations(1);
            ops.push(std::make_shared<Operation>(value));
        }

        ++begin;
    }

    while(!ops.empty())
    {
        PopupOperations(0);
    }
    
    return values.top();
}


