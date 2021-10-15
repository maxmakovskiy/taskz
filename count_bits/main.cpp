#include <iostream>
#include <vector>

typedef unsigned long long ull;

std::vector<ull> to_bin(ull decimal)
{
    std::vector<ull> digits;

    while(decimal >= 0)
    {
        digits.push_back(decimal % 2);
        decimal /= 2;

        if (decimal == 0)
            break;
    }

    return digits;
}

unsigned int countBits(ull n)
{
    unsigned int result = 0;
    std::vector<ull> tmp = to_bin(n);

    while(tmp.begin() != tmp.end())
    {
        result = result + tmp.back();
        tmp.pop_back();
    }

    return result;
}

int main()
{
    std::cout << "countBits(5): " << countBits(5) << std::endl;
    return 0;
}
