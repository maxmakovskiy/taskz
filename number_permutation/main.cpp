#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::vector<int>> GetAllPermutation(int number)
{
    std::vector<std::vector<int>> result;

    std::vector<int> source;
    for(int i = 1; i <= number; i++)
    {
        source.push_back(i);
    }
    result.push_back(source);

    while(std::next_permutation(source.begin(), source.end()))
    {
        result.push_back(source);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v)
{
    os << "[";

    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it+1 == v.end())
        {
            os << *it << "]";
            break;
        }

        os << *it << ", ";
    }
    
    return os;
}

int main()
{
    auto result = GetAllPermutation(3);

    for (const auto& str : result)
    {
        std::cout << str << std::endl;
    }


    return 0;
}
