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

    template <typename U>
    struct Access 
    {
        std::lock_guard<std::mutex> guard;
        U& ref_to_value;
    };

    Access<T> GetAccess()
    {
        return {std::lock_guard<std::mutex>(m), value};
    }

    Access<const T> GetAccess() const
    {
        return {std::lock_guard<std::mutex>(m), value};
    }

private:
    T value;
    mutable std::mutex m;

};


