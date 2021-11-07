#include <iostream>
#include <vector>

template <typename Iterator>
struct IteratorRange 
{
    Iterator first;
    Iterator last;

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

template <typename T>
IteratorRange<typename std::vector<T>::iterator> Head(
        std::vector<T>& v, size_t top
)
{
    return {
        v.begin(), std::next(v.begin(), std::min(top, v.size()))
    };
}

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    for (int& x : Head(v, 3))
    {
        x++;
    }
    
    for (int x : v)
    {
        std::cout << x << ' '; 
    }

    std::cout << std::endl;
    
    std::cout << "Range size = " << RangeSize(Head(v, 3)) << std::endl;


    return 0;
}
