//
// Created by obnitram on 27/09/24.
//

#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include <forward_list>
#include <vector>


template <typename K, typename V>
class HashMap
{
    struct Entry
    {
        K key;
        V value;
    };

    const size_t bukets_size = 10000;

    std::vector<std::forward_list<Entry>> buckets;
    size_t _size;

public:
    HashMap() : buckets(bukets_size), _size(0)
    {
    }

    V get(const K& key)
    {
        size_t index = std::hash<K>{}(key) % bukets_size;
        for (auto& [_key,_value] : buckets[index])
        {
            if (_key == key)
            {
                return _value;
            }
        }
        return 0;
    }

    void put(const K& key, const V& value)
    {
        size_t index = std::hash<K>{}(key) % bukets_size;
        for (auto& [_key,_value] : buckets[index])
        {
            if (_key == key)
            {
                _value = value;
                return;
            }
        }
        buckets[index].push_front({key, value});
        _size++;
    }

    size_t getSize() const
    {
        return _size;
    }
};


#endif //HASHMAP_HPP
