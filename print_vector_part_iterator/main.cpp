#include <iostream>
#include <algorithm>
#include <vector>

void PrintVectorPart(const std::vector<int>& numbers)
{
    std::vector<int>::const_iterator neg_number_it = std::find_if(
            numbers.begin(), numbers.end(), [] (int n) {
            return n < 0;
            });

    if (neg_number_it == numbers.end())
    {
        for (auto it = numbers.rbegin(); it != numbers.rend(); it++)
            std::cout << *it << " ";
    }
    else
    {
        while(neg_number_it != numbers.begin())
        {
            neg_number_it--;
            std::cout << *neg_number_it << " ";
        }
    }

    std::cout << std::endl;
}
int main()
{
    PrintVectorPart({6, 1, 8, -4, -3});
    PrintVectorPart({6, 1, 8, 4, 3});
}
