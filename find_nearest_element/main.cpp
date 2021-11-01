#include <iostream>
#include <set>
#include <iterator>

std::set<int>::const_iterator FindNearestElement(const std::set<int>& numbers, int border)
{
    if (numbers.size() == 0) return numbers.end();

    if (numbers.count(border) > 0) return numbers.find(border);

    if (*numbers.rbegin() < border)
    {
        auto itGreather = std::next(numbers.begin(), numbers.size()-1);
        return itGreather;
    }

    auto itUpper = numbers.lower_bound(border);
    if (itUpper == numbers.begin()) return itUpper;

    auto itLower = std::prev(numbers.lower_bound(border));

    int toUpperDist = *itUpper - border;
    int toLowerDist = border - *itLower;
    
    if (toUpperDist >= toLowerDist) return itLower;
    
    return itUpper;
}

int main()
{
    std::set<int> numbers = {1, 4, 6};

    std::cout <<
        *FindNearestElement(numbers, 0) << " " <<
        *FindNearestElement(numbers, 3) << " " <<
        *FindNearestElement(numbers, 5) << " " <<
        *FindNearestElement(numbers, 6) << " " <<
        *FindNearestElement(numbers, 100) << std::endl;

    std::set<int> empty_set;
    std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;

    return 0;
}
