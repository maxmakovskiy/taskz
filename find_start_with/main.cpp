#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix)
{

    RandomIt d_begin, d_end;


    d_begin = std::lower_bound(range_begin, range_end, std::string(1, prefix));

    char nextChar = static_cast<char>(prefix + 1);
    d_end = std::lower_bound(range_begin, range_end, std::string(1, nextChar));

    return std::make_pair(d_begin, d_end);

/*
    RandomIt d_begin, d_end;

    d_begin = std::find_if(range_begin, range_end, 
        [prefix] (const std::string& s) {
            return s[0] == prefix;
    });

    d_end = std::find_if(d_begin, range_end, 
        [prefix] (const std::string& s) {
            return s[0] != prefix;
    });

    return std::make_pair(d_begin, d_end);
*/

/*
    RandomIt d_begin, d_end;

    d_begin = std::find_if(range_begin, range_end, 
        [prefix] (const std::string& s) {
            return s[0] == prefix;
    });

    for (auto first = d_begin; first != range_end; first++)
    {
        if ((*first)[0] != prefix) 
        {
            d_end = first;
            break;
        }
    }

    return std::make_pair(d_begin, d_end);
*/
}

int main()
{

    const std::vector<std::string> sorted_strings = {"moscow", "murmansk", "n", "nirvana", "vologda"};

    const auto m_result = 
        FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto m_result_2 = 
        FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'n');
    for (auto it = m_result_2.first; it != m_result_2.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto p_result = 
        FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'p');
    std::cout << (p_result.first - std::begin(sorted_strings)) << " " <<
        (p_result.second - std::begin(sorted_strings)) << std::endl;

    const auto z_result =
        FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), 'z');
    std::cout << (z_result.first - std::begin(sorted_strings)) << " " <<
        (z_result.second - std::begin(sorted_strings)) << std::endl;

    return 0;
}
