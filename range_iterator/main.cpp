#include <iostream>
#include <vector>
#include <set>
#include <deque>

template <typename Iterator>
struct IteratorRange 
{
    Iterator first;
    Iterator last;

    IteratorRange(Iterator first, Iterator last)
    {
        this->first = first;
        this->last = last;
    }

    Iterator begin() const
    {
        return first;
    }

    Iterator end() const
    {
        return last;
    }

};

template <typename T>
size_t RangeSize(IteratorRange<T> r)
{
    return r.end() - r.begin(); 
}

template <typename Container>
auto Head(
        Container& c, size_t top
)
{
    return IteratorRange(
        c.begin(), std::next(c.begin(), std::min(top, c.size()))
    );
}

template <typename Iterator>
IteratorRange<Iterator> make_range(Iterator begin, Iterator end)
{
    return IteratorRange<Iterator>(begin, end);
}

int main()
{
    std::cout << "VECTOR:" << std::endl;
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (int x : Head(v, 4))
    {
        std::cout << x << ' '; 
    }
    std::cout << std::endl;

    std::cout << "SET:" << std::endl;
    std::set<int> numbers = {12, 3, 44, 1, 534};
    for (int x : Head(numbers, 4))
    {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "Deque:" << std::endl;
    std::deque<int> queueNums = {2, 3, 1, 2, 5, 6, 83, 45, 2, 3};
    for (int x : Head(queueNums, 4))
    {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "CONST Deque:" << std::endl;
    const std::deque<int> constQueueNums = {2, 3, 1, 2, 5, 6, 83, 45, 2, 3};
    for (int x : Head(constQueueNums, 4))
    {
        std::cout << x << ' ';
    }
    std::cout << std::endl;


    return 0;
}
