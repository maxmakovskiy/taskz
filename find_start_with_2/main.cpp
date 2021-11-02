#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const std::string& prefix)
{
    RandomIt d_begin, d_end;

    d_begin = std::lower_bound(range_begin, range_end, prefix);

    d_end = std::find_if(range_begin, range_end,
        [prefix](const std::string& s) {
            return prefix < s.substr(0, prefix.size());
        });


    return std::make_pair(d_begin, d_end);

}

int main()
{

    const std::vector<std::string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
    const auto mo_result =
        FindStartsWith(std::begin(sorted_strings), std::end(sorted_strings), "mo");

    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    std::cout << (mt_result.first - std::begin(sorted_strings)) << " " <<
        (mt_result.second - std::begin(sorted_strings)) << std::endl;

    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    std::cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << std::endl;

    return 0;
}
