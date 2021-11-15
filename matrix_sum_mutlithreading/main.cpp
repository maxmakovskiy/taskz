#include "test.h"
#include "paginate.h"
#include <vector>
#include <future>
#include <cstdint>
#include <algorithm>

int64_t CalculateMatrixSum(const std::vector<std::vector<int>>& matrix) 
{
    int64_t result = 0;
    size_t page_size = 2;
    
    std::vector<std::future<int>> fs;
    for (const auto& page : Paginate(matrix, page_size)) {
        for (const auto& row : page) {
//            result += std::accumulate(row.begin(), row.end(), 0);
            fs.push_back(std::async(
                    std::launch::async,
                    [&row] { 
                        return std::accumulate(row.begin(), row.end(), 0);
                    }));
        }
    }

    for (auto& f : fs) {
        result += f.get();
    }
    return result;
}

void TestCalculateMatrixSum() 
{
  const std::vector<std::vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);

    return 0;
}
