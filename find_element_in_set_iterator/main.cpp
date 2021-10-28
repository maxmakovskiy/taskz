#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

template <typename T>
std::vector<T> FindGreaterElements(const std::set<T>& elements, const T& border)
{
    auto pos = std::find(elements.begin(),
            elements.end(), border);
    
    std::vector<T> result;

    if (pos == elements.end()) return result;

    pos++; // skip current element
    for (; pos != elements.end(); pos++)
    {
        result.push_back(*pos);
    }

    return result;
}


int main()
{
    for (int x : FindGreaterElements(std::set<int>{1, 5, 7, 8}, 5))
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    
    std::string target = "Python";
    std::cout << FindGreaterElements(std::set<std::string>{"C", "C++"}, target).size() << std::endl;

    return 0;
}
