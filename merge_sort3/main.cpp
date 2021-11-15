#include "test.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <string>
#include <iterator>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) 
{
    if (std::distance(range_begin, range_end) < 2) {
        return;
    }
    
    std::vector<typename RandomIt::value_type> elements(
            std::make_move_iterator(range_begin),
            std::make_move_iterator(range_end));
    auto pos1 = elements.begin() + elements.size() / 3;
    auto pos2 = pos1 + elements.size() / 3;

    MergeSort(elements.begin(), pos1);
    MergeSort(pos1, pos2);
    MergeSort(pos2, elements.end());

    std::vector<typename RandomIt::value_type> temporary;
    std::merge(std::make_move_iterator(elements.begin()), 
            std::make_move_iterator(pos1),
            std::make_move_iterator(pos1), 
            std::make_move_iterator(pos2), 
            std::back_inserter(temporary));
    std::merge(std::make_move_iterator(temporary.begin()),
            std::make_move_iterator(temporary.end()), 
            std::make_move_iterator(pos2), 
            std::make_move_iterator(elements.end()), 
            range_begin);
}

class StringNonCopyable : public std::string {
public:
  using std::string::string;
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestIntVector() 
{
    std::vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(std::begin(numbers), std::end(numbers));
    ASSERT(std::is_sorted(std::begin(numbers), std::end(numbers)));
}

void TestOdinaryStrings() 
{
    std::vector<std::string> strs = { "first", "apple", "in", "world", "the" };
    MergeSort(std::begin(strs), std::end(strs));
    ASSERT(std::is_sorted(std::begin(strs), std::end(strs)));
}

void TestStringNonCopyable() 
{
    std::vector<StringNonCopyable> strs;
    
    strs.push_back("first");
    strs.push_back("apple");
    strs.push_back("in");
    strs.push_back("world");
    strs.push_back("the");

    MergeSort(std::begin(strs), std::end(strs));
    ASSERT(std::is_sorted(std::begin(strs), std::end(strs)));
}


int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestOdinaryStrings);
    RUN_TEST(tr, TestStringNonCopyable);


    return 0;
}
