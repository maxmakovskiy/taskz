#pragma once

#include <functional>
#include <optional>

template <typename T>
class LazyValue 
{
public:
    explicit LazyValue(std::function<T()> init)
        : creator(std::move(init))
    {
    }

    bool HasValue() const
    {
        return value.has_value();
    }

    const T& Get() const
    {
        if (value) {
            return *value;
        }
        
        value = creator();
        return *value;
    }

private:
    std::function<T()> creator;
    mutable std::optional<T> value;

};


