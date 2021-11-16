#pragma once
#include <mutex>

template <typename T>
T abs(T val) 
{
    return val < 0 ? -val : val;
}

auto lock(std::mutex& m)
{
    return std::lock_guard<std::mutex>(m);
}

template <typename K, typename V>
class ConcurrentMap 
{
public:
    static_assert(std::is_integral_v<K>,
            "ConcurrentMap supports only integer keys");

    struct Access 
    {
        std::lock_guard<std::mutex> guard;
        V& ref_to_value;

        Access(const K& key, std::pair<std::mutex, std::map<K, V>>& bucket)
            : guard(bucket.first)
            , ref_to_value(bucket.second[key])
        {}
    };

    explicit ConcurrentMap(size_t bucket_count)
        : base(bucket_count)
    {
    }

    Access operator[](const K& key)
    {
        // determine which bucket we need to use !
       
        // if element with given key doesn't exist in any bucket
        // then we write them to first backet
        size_t bucket_idx = abs(key) % base.size();
        std::pair<std::mutex, std::map<K,V>>& bucket = base[bucket_idx];
        
        return { key, bucket }; 
    }

    std::map<K, V> BuildOrdinaryMap()
    {
        std::map<K, V> result;
        for (auto& [_mutex, _map] : base) {
            auto guard = lock(_mutex);
            result.insert(_map.begin(), _map.end()); 
        }
        return result;
    }

private:
    // save for each bucket own mutex
    std::vector<std::pair<std::mutex, std::map<K, V>>> base;
};

