#include <iostream>
#include <algorithm>
#include <iterator>

#include "profiler.h"

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (std::distance(range_begin, range_end) < 2)
    {
        return;
    }

    std::vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto middle = elements.begin() + elements.size() / 2;
    MergeSort(elements.begin(), middle);
    MergeSort(middle, elements.end());

    std::merge(elements.begin(), middle, middle, elements.end(), range_begin);

}

int main()
{
    std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};

    {
        LOG_DURATION("MergeSort");
        MergeSort(std::begin(v), std::end(v));
    }

    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

