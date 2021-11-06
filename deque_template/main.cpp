#include "test.h"
#include <vector>
#include <stdexcept>

template <typename T>
class Deque
{
public:
    Deque()
    {
    }
    
    bool Empty() const
    {
        return head.empty() && tail.empty();
    }

    size_t Size() const
    {
        return head.size() + tail.size();
    }

    // without bound checking
    const T& operator[](size_t idx) const
    {
        return at(idx);
    } 

    T& operator[](size_t idx)
    {
        return at(idx);
    }

    // bound checking
    // if idx > size()-1 then throw out_of_range exception
    const T& At(size_t idx) const
    {
        checkIndex(idx);
        return at(idx);
    } 

    T& At(size_t idx)
    {
        checkIndex(idx);
        return at(idx);
    }

    const T& Front() const
    {
        return head.empty() ? tail.front() : head.back();
    }
    
    T& Front()
    {
        return head.empty() ? tail.front() : head.back();
    }

    const T& Back() const
    {
        return tail.empty() ? head.front() : tail.back();
    }

    T& Back()
    {
        return tail.empty() ? head.front() : tail.back();
    }
    
    void PushBack(T val)
    {
        tail.push_back(val);
    }

    void PushFront(T val)
    {
        head.push_back(val);
    }

private:
//  |(back)    head    (front)|(front)    tail    (back)|
    std::vector<T> head, tail;

    void checkIndex(size_t idx) const
    {
        if (idx >= Size()) throw std::out_of_range("Index is out of range");
    }
    
    T& at(size_t idx)
    {
        return idx < head.size() 
            ? head[head.size()-1-idx] : tail[idx-head.size()];
    }

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

