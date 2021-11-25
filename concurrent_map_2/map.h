#pragma once
#include <mutex>
#include <unordered_map>
#include <vector>

template <typename K, typename V, typename Hash = std::hash<K>>
class ConcurrentMap 
{
public:
    using MapType = std::unordered_map<K, V, Hash>;

    explicit ConcurrentMap(size_t bucket_count)
        : base(bucket_count)
    {
    }

    struct ReadAccess
    {
        std::lock_guard<std::mutex> g;
        const V& ref_to_value;
    };

    struct WriteAccess 
    {
        std::lock_guard<std::mutex> guard;
        V& ref_to_value;
    };

    // Represent chunck of whole cocurrent hash map
    struct Bucket
    {
        mutable std::mutex m;
        MapType chunk;

        WriteAccess GetValue(const K& key)
        {
            return { std::lock_guard(m), chunk[key] };
        }

        ReadAccess GetValue(const K& key) const
        {
            return { std::lock_guard(m), chunk.at(key) };
        }

        bool Has(const K& key) const
        {
            return chunk.count(key) > 0;
        }
    };


    WriteAccess operator[](const K& key)
    {
        return GetBucket(key).GetValue(key);
    }

    ReadAccess At(const K& key) const
    {
        return GetBucket(key).GetValue(key);
    }

    bool Has(const K& key) const
    {
        return GetBucket(key).Has(key);
    }
    
    MapType BuildOrdinaryMap() const
    {
        MapType result;
        for (const Bucket& b : base)
        {
            std::lock_guard<std::mutex> lock(b.m);
            for (const auto& [key, value] : b.chunk) {
                result[key] = value;
            }
        }
        
        return result;
    }


private:
    Hash hasher;
    std::vector<Bucket> base;

    const Bucket& GetBucket(const K& key) const
    {
        return base[hasher(key) % base.size()];
    }

    Bucket& GetBucket(const K& key) 
    {
        return base[hasher(key) % base.size()];
    }


};

