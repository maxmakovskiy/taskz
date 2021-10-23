#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

bool ByPassReg(const std::string& s1, const std::string& s2)
{
    char t1 = tolower(s1[0]);
    char t2 = tolower(s2[0]);
    if (t1 < t2)
    {
        return true;
    }
    
    return false;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::string> strings(n);

    for (auto& el : strings)
    {
        std::cin >> el;
    }

    std::sort(std::begin(strings), std::end(strings), ByPassReg);

    std::cout << "Sorted array" << std::endl;
    for (const auto& el : strings)
    {
        std::cout << el << "; ";
    }
    std::cout << std::endl;


    return 0;
}
