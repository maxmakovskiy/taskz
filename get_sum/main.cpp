#include <iostream>

int get_sum(int a, int b)
{
    if (a == b) return a;
    
    int result = 0;
    int steps, temp;

    if (a > b)
    {
        steps = a - b;
        temp = b;
        for (int i = 0; i < steps + 1; i++)
        {
            result += temp;
            temp++;
        }
    }
    else
    { // a < b
        steps = b - a;
        temp = a;
        for (int i = 0; i < steps + 1; i++)
        {
            result += temp;
            temp++;
        }
    }

    return result;
}

int main()
{
    std::cout << "get_sum(1, 0): " << get_sum(1, 0) << std::endl;
    std::cout << "get_sum(1, 2): " << get_sum(1, 2) << std::endl;
    std::cout << "get_sum(0, 1): " << get_sum(0, 1) << std::endl;
    std::cout << "get_sum(1, 1): " << get_sum(1, 1) << std::endl;
    std::cout << "get_sum(-1, 0): " << get_sum(-1, 0) << std::endl;
    std::cout << "get_sum(-1, 2): " << get_sum(-1, 2) << std::endl;

    return 0;
}
