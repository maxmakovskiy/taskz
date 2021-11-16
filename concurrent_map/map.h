#pragma once
#include <mutex>

template <typename K, typename V>
class ConcurrentMap 
{
public:
    static_assert(std::is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access 
    {
        std::lock_guard<std::mutex> guard;
        V& ref_to_value;
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
        size_t bucket_idx = 0;

        for (size_t i = 0; i < base.size(); i++) {
            if (base[i].find(key) != base[i].end()) {
                bucket_idx = i;
            }
        }
        
        return { std::lock_guard<std::mutex>(m), base[bucket_idx][key]};
    }

    std::map<K, V> BuildOrdinaryMap()
    {
        std::lock_guard<std::mutex> g(m);
        std::map<K, V> result;
        for (const auto& m : base) {
            result.insert(m.begin(), m.end()); 
        }
        return result;
    }



private:
    std::vector<std::map<K, V>> base;
    std::mutex m;
};

