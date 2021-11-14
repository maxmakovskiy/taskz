#include "test.h"

#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
#include <map>

using Group = std::vector<std::string>;

std::string computeUniqueChars(const std::string& source)
{
    std::string result(source);
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

std::vector<Group> GroupHeavyStrings(std::vector<std::string> strings) 
{
    std::vector<Group> result;
    std::map<std::string, Group> groups;
    for (std::string& s : strings) {
        groups[computeUniqueChars(s)].push_back(std::move(s));
    }
    for (auto& [key, value] : groups) {
        result.push_back(std::move(value));
    }

    return result; 
}

void TestGroupingABC() 
{
    std::vector<std::string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    std::sort(std::begin(groups), std::end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({"caab", "abc", "bacc"}));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({"cccc", "c"}));
}

void TestGroupingReal() 
{
    std::vector<std::string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    std::sort(std::begin(groups), std::end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({"laptop", "paloalto"}));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({"law", "wall", "awl"}));
    ASSERT_EQUAL(groups[2], std::vector<std::string>({"port"}));
    ASSERT_EQUAL(groups[3], std::vector<std::string>({"top", "pot"}));
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestGroupingABC);
  RUN_TEST(tr, TestGroupingReal);

  return 0;
}
