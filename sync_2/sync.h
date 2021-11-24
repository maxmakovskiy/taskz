#pragma once

#include <mutex>

template <typename T>
class Synchronized 
{
public:
    explicit Synchronized(T initial = T())
        : value(std::move(initial))
    {
    }

    struct Access1 
    {
        std::lock_guard<std::mutex> guard;
        T& ref_to_value;
    };

    struct Access2 
    {
        std::lock_guard<std::mutex> guard;
        const T& ref_to_value;
    };

    Access1 GetAccess()
    {
        return {std::lock_guard<std::mutex>(m), value};
    }

    Access2 GetAccess() const
    {
        return {std::lock_guard<std::mutex>(m), value};
    }

private:
    T value;
    std::mutex m;

};


