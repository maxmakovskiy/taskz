#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename T>
void RemoveDuplicates(std::vector<T>& elements)
{
    // Firstly, make duplicate elements consecutive
    std::sort(elements.begin(), elements.end());

    // Eliminates all except the first element from every consecutive group of equivalent elements
    auto firstDuplicatePos = std::unique(elements.begin(), elements.end());

    // delete duplicate elements
    elements.erase(firstDuplicatePos, elements.end());
}

int main()
{
    std::vector<int> v1 = {6, 4, 7, 6, 4, 4, 0, 1};

    RemoveDuplicates(v1);
    for (int x : v1) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> v2 = {"C", "C++", "C++", "C", "C++"};

    RemoveDuplicates(v2);
    for (const std::string& s : v2) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    return 0;
}
