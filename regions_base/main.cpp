#include <iostream>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
#include <tuple>
#include <algorithm>

enum class Lang
{
    DE, FR, IT
};

struct Region
{
    std::string std_name;
    std::string parent_std_name;
    std::map<Lang, std::string> names;
    int64_t population;
};

bool operator<(const Region& lhs, const Region& rhs)
{
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population)
        < tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);

}

int FindMaxRepetitionCount(const std::vector<Region>& regions)
{
    int result = 0;
    std::map<Region, int> unique;
    for (const auto& region : regions)
    {
        unique[region]++;
        result = std::max(result, unique[region]);
    }
    
    return result;
}

int main()
{
    std::vector<Region> regions = {
        {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Moscow",
            "Russia",
            {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
            89
        }, {
            "Russia",
            "Eurasia",
            {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
            89
        },
    };

    std::cout << FindMaxRepetitionCount(regions) << std::endl;

    return 0;
}
