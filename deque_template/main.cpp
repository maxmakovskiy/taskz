#include "test.h"
#include <vector>

template <typename T>
class Deque
{
public:
    Deque()
        : elementsNumber(0)
    {
    }
    
    bool Empty() const
    {
        return data.empty();
    }

    size_t Size() const
    {
        return elementsNumber;
    }

    // without bound checking
    const T& operator[](size_t idx) const
    {
        return data.at(idx);
    } 

    T& operator[](size_t idx)
    {
        return data[idx];
    }

    // bound checking
    // if idx > size()-1 then throw out_of_range exception
    const T& At(size_t idx) const
    {
        return data.at(idx);
    } 

    T& At(size_t idx)
    {
        return data.at(idx);
    }

    const T& Front() const
    {
        return data.front();
    }
    
    T& Front()
    {
        return data.front();
    }

    const T& Back() const
    {
        return data.back();
    }

    T& Back()
    {
        return data.back();
    }
    
    void PushBack(T val)
    {
        elementsNumber++;
        data.push_back(val);
    }

    void PushFront(T val)
    {
        elementsNumber++;
        data.insert(data.begin(), val);
    }

private:
    size_t elementsNumber;
    std::vector<T> data;
    
};

void TestDeque()
{
    Deque<int> deque;
    ASSERT(deque.Empty());
    ASSERT_EQUAL(deque.Size(), 0);
    
    for (int i = 1; i <= 5; i++)
    {
        deque.PushBack(i);
    }
    ASSERT_EQUAL(deque.Size(), 5);

    ASSERT_EQUAL(deque.Front(), 1);
    deque.Front() = 11;
    ASSERT_EQUAL(deque.Front(), 11);

    for (int i = 1; i <= 5; i++)
    {
        deque.PushFront(i);
    }
    ASSERT_EQUAL(deque.Size(), 10);

    ASSERT_EQUAL(deque.Back(), 5);
    deque.Back() = 31;
    ASSERT_EQUAL(deque.Back(), 31);

    deque[0] = 111;
    ASSERT_EQUAL(deque[0], 111);

    deque.At(1) = 222;
    ASSERT_EQUAL(deque.At(1), 222);

}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestDeque);

    return 0;
}

