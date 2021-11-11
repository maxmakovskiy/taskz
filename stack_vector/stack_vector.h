#pragma once

#include <stdexcept>
#include <array>

template <typename T, size_t N>
class StackVector 
{
public:
    explicit StackVector(size_t a_size = 0)
        : _size(a_size)
        , _capacity(N)
    {
        if (a_size > N) throw std::invalid_argument("");
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data.at(index); }

    typename std::array<T, N>::iterator begin()
    {
        return data.begin();
    }
    typename std::array<T, N>::iterator end()
    {
        return data.end();
    }

    typename std::array<T, N>::const_iterator begin() const
    {
        return data.begin();
    }

    typename std::array<T, N>::const_iterator end() const
    {
        return data.end();
    }

    size_t Size() const { return _size; }
    size_t Capacity() const { return _capacity; }

    void PushBack(const T& value)
    {
        if(_capacity == _size) throw std::overflow_error(""); 

        data[_size] = value;
        _size++;
    }

    T PopBack()
    {
        if (_size == 0) throw std::underflow_error("");
        
        T last = data[_size-1];
        _size--;
        return last;
    }

private:
    std::array<T, N> data;
    size_t _size = 0;
    size_t _capacity = 0;

};

