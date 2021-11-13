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
        this->size = other.size;
        this->capacity = other.capacity;

        data = new T[this->capacity];
        std::copy(other.begin(), other.end(), this->begin());
    }

    const SimpleVector& operator=(const SimpleVector& other)
    {
        this->size = other.size;
        this->capacity = other.capacity;
        delete[] data;
        data = new T[this->capacity];

        for (size_t i = 0; i < size; i++) {
            data[i] = other[i];
        }

        return *this;
    }
   
    ~SimpleVector()
    {
        delete[] data;
    }

    T& operator[](size_t index) { return *(data + index); }
    const T& operator[](size_t index) const { return *(data + index); }

    T* begin() { return data; }

    T* end() { return (data + size); }

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
