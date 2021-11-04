#include <iostream>

#include "parser.h"

int main()
{
    std::string tokens;
    std::cout << "Enter expression: ";
    std::getline(std::cin, tokens);
    
    int x = 0;
    auto node = Parse(tokens.begin(), tokens.end(), x);

    std::cout << "Enter x: ";
    while (std::cin >> x)
    {
        std::cout << "Expression value: " << node->Evaluate() << std::endl;
        std::cout << "Enter x: ";
    }

    return 0;
}
