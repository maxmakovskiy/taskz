#include "expr.h"

std::string ExpressionManager::ToString()
{
    std::string result;

    Expression copy = expression;
    while (!copy.empty())
    {
        auto element = copy.front();
        copy.pop();

        if (element.op == OpType::SOURCE)
        {
            result += "(" + std::to_string(element.source) + ")";
            continue;
        }

    if (copy.empty())
    {
        result += " " + std::string(1, element.opSymbol) + " " + std::to_string(element.source);
        break;
    }

        result += " " + std::string(1, element.opSymbol) + " " + std::to_string(element.source) + ")";
        result.insert(0, "(");
    }

    return result;
}

void ExpressionManager::AddExp(std::string raw)
{
    if (raw.size() == 1)
    {
        AddPart(std::stoi(raw), OpType::SOURCE, 0);
        return;
    }

    // else raw.size() == 3
    OpType type; 
    if (raw[0] == '+') {
        type = OpType::ADD;
    }
    else if (raw[0] == '-') {
        type = OpType::SUB;
    }
    else if (raw[0] == '*') {
        type = OpType::MULT;
    }
    else if (raw[0] == '/') {
        type = OpType::DIV;
    }
    else {
        type = OpType::SOURCE;
    }

    int value = std::stoi(raw.substr(2));

    AddPart(value, type, raw[0]);
}

void ExpressionManager::AddPart(int val, OpType op, char opSymbol)
{
    expression.push(ExprStruct(val, op, opSymbol));
}

double ExpressionManager::Evaluate()
{
    double result;

    while (!expression.empty())
    {
        auto element = expression.front();
        expression.pop();

        switch (element.op)
        {
        case OpType::SOURCE:
            result = element.source;
            break;
        case OpType::ADD:
            result += element.source;
            break;
        case OpType::SUB:
            result -= element.source;
            break;
        case OpType::MULT:
            result *= element.source;
            break;
        case OpType::DIV:
            result /= element.source;
            break;
        }
    }

    return result;
}
