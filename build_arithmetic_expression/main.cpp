#include <iostream>

#include "expr.h"

int main()
{
    ExpressionManager manager;
    manager.AddExp("8");
    manager.AddExp("* 3");
    manager.AddExp("- 6");
    manager.AddExp("/ 1");
    std::cout << manager.ToString() << " = " 
        << manager.Evaluate() << std::endl;


    return 0;
}
