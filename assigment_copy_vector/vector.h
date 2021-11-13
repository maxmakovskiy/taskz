#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
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
    
    SimpleVector(const SimpleVector& other)
    {
        size = other.size;
        capacity = other.capacity;

        data = new T[capacity];
        std::copy(other.begin(), other.end(), begin());
    }

    void operator=(const SimpleVector& other)
    {
        if (other.size <= capacity) {
            std::copy(other.begin(), other.end(), begin());
            size = other.size;
        } else {
            // Copy-And-Swap
           
            SimpleVector<T> temporary(other);
            std::swap(temporary.data, data); 
            std::swap(temporary.size, size); 
            std::swap(temporary.capacity, capacity); 
        }
    }
   
    ~SimpleVector()
    {
        delete[] data;
    }

    T& operator[](size_t index) { return *(data + index); }
    const T& operator[](size_t index) const { return *(data + index); }

    T* begin() { return data; }
    T* end() { return (data + size); }

    const T* begin() const { return data; }
    const T* end() const { return (data + size); }

    size_t Size() const { return size; }
    size_t Capacity() const { return capacity; }

    void PushBack(const T& value)
    {
        if (!data) {
            capacity = 1u;
            data = new T[capacity];
        } else if (size == capacity) {
            capacity *= 2;
            T* newLocation = new T[capacity];
            std::copy(begin(), end(), newLocation);
            delete[] data;
            data = newLocation;
        }

        *(data + size) = value;
        size++;
    }

private:
    size_t size = 0u;
    size_t capacity = 0u;
    T* data = nullptr;
};
