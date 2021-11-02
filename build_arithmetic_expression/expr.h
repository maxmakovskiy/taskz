#pragma once

#include <string>
#include <queue>

enum class OpType : int
{
    ADD, SUB, MULT, DIV, SOURCE
};

struct ExprStruct
{
    int source;
    char opSymbol;
    OpType op;

    ExprStruct(int source, OpType op, char opSymbol)
    {
        this->source = source;
        this->op = op;
        this->opSymbol = opSymbol;
    }

};

using Expression = std::queue<ExprStruct>;

class ExpressionManager
{
public:
    std::string ToString();

    double Evaluate();

    void AddExp(std::string raw);

private:
    Expression expression;

    void AddPart(int val, OpType op, char opSymbol);

};

