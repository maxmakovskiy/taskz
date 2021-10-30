#include <iostream>
#include <algorithm>
#include <iterator>

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (std::distance(range_begin, range_end) < 2)
    {
        return;
    }

    std::vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto pos1 = elements.begin() + elements.size() / 3;
    auto pos2 = pos1 + elements.size() / 3;
   
    MergeSort(elements.begin(), pos1);
    MergeSort(pos1, pos2);
    MergeSort(pos2, elements.end());
    
    std::vector<typename RandomIt::value_type> temp;
    std::merge(elements.begin(), pos1, pos1, pos2, std::back_inserter(temp));
    std::merge(temp.begin(), temp.end(), pos2, elements.end(), range_begin);

}

int main()
{
    std::vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};

    MergeSort(std::begin(v), std::end(v));

    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}

