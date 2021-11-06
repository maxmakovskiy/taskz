#include "test.h"

#include <vector>
#include <utility>

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table
{
public:
    Table(size_t rowsNumber, size_t colomnsNumber)
        : rowsNumber(rowsNumber)
        , colomnsNumber(colomnsNumber)
    {
        Resize(rowsNumber, colomnsNumber);
    }

    const std::vector<T>& operator[](size_t row) const
    {
        return content.at(row);
    }

    std::vector<T>& operator[](size_t row)
    {
        return content[row];
    }

    void Resize(size_t rowsNumber, size_t colomnsNumber)
    {
        this->rowsNumber = rowsNumber;
        this->colomnsNumber = colomnsNumber;
        content.resize(rowsNumber);
        
        for (auto& row : content)
        {
            row.resize(colomnsNumber);
        }

    }

    std::pair<size_t, size_t> Size() const
    {
        return std::make_pair(rowsNumber, colomnsNumber);
    }

private:
    size_t rowsNumber;
    size_t colomnsNumber;
    std::vector<std::vector<T>> content;

};


void TestTable() {
    Table<int> t(1, 1);

    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);

    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);

    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);

    return 0;
}
