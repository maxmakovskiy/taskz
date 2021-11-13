#pragma once

#include <cstdlib>
#include <algorithm>

template <typename T>
class SimpleVector 
{
public:
    SimpleVector() {}
    explicit SimpleVector(size_t size)
    {
        this->size = size;
        this->capacity = size * 2;
        data = new T[capacity];
    }

    ~SimpleVector()
    {
        delete[] data;
    }

    T& operator[](size_t index) { return *(data + index); }

    T* begin() { return data; }

    T* end() { return (data + size); }

    size_t Size() const { return size; }

    size_t Capacity() const { return capacity; }

    void PushBack(T value)
    {
        if (!data) {
            capacity = 1u;
            data = new T[capacity];
        } else if (size == capacity) {
            capacity *= 2;
            T* newLocation = new T[capacity];
            std::move(begin(), end(), newLocation);
            delete[] data;
            data = newLocation;
        }

        *(data + size) = std::move(value);
        size++;
    }

private:
    size_t size = 0u;
    size_t capacity = 0u;
    T* data = nullptr;
};
