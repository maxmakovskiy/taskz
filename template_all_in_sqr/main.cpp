#include <iostream>
#include <vector>
#include <map>
#include <utility>


template<typename T>
std::vector<T> Sqr(const std::vector<T>& v)
{
    std::vector<T> result;
    
    for (const T& el : v)
    {
        result.push_back(el*el); 
    }

    return result;
}

template<typename Key, typename Value>
std::map<Key, Value> Sqr(const std::map<Key, Value>& m)
{
    std::map<Key, Value> result;
    
    for (const auto& el : m)
    {
        result[el.first] = el.second * el.second; 
    }

    return result;
}

template<typename First, typename Second>
std::pair<First, Second> Sqr(const std::pair<First, Second>& p)
{
    return std::make_pair(p.first*p.first, p.second*p.second);
}

template<typename First, typename Second>
std::pair<First, Second> operator*(const std::pair<First, Second>& lhs, const std::pair<First, Second>& rhs)
{
    return std::make_pair(lhs.first*rhs.first, lhs.second*rhs.second);
}

int main()
{

    std::vector<int> v = {1, 2, 3};

    std::cout << "vector:";
    for (int x : Sqr(v)) {
        std::cout << ' ' << x;
    }
    std::cout << std::endl;

    std::map<int, std::pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };

    std::cout << "map of pairs:" << std::endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        std::cout << x.first << ' ' << x.second.first << ' ' << x.second.second << std::endl;
    }

    return 0;
}
