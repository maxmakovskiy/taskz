#include "test.h"
#include "profiler.h"
#include "paginate.h"
#include <vector>
#include <future>
#include <cstdint>
#include <algorithm>

template <typename ContainerOfVectors>
int64_t SumOfPartOfMatrix(const ContainerOfVectors& matrix) {
  int64_t sum = 0;
  for (const auto& row : matrix) {
    for (auto item : row) {
      sum += item;
    }
  }
  return sum;
}

int64_t
CalculateMatrixSum
(const std::vector<std::vector<int>>& matrix, size_t page_size) 
{
    int64_t result = 0;
    
    std::vector<std::future<int64_t>> fs;

    for (const auto& page : Paginate(matrix, page_size)) {
        fs.push_back(std::async([=]{ return SumOfPartOfMatrix(page); }));
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
  ASSERT_EQUAL(CalculateMatrixSum(matrix, 2), 136);
//  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

void TestBench()
{
    std::vector<std::vector<int>> matrix(9000);
    for (auto& v : matrix) {
        v.resize(100);
        std::iota(v.begin(), v.end(), 1);
    } 

    {
        LOG_DURATION_MILLISECONDS("9000 x 100 matrix sum");
        CalculateMatrixSum(matrix, 300);
//        CalculateMatrixSum(matrix);
    }

}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
    RUN_TEST(tr, TestBench);

    return 0;
}
