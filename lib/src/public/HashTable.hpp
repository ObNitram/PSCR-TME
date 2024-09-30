#pragma once
#include "List.hpp"
#include "Vector.hpp"

#include <cstddef>
#include <functional>

namespace pscr
{
template <typename K, typename V> class HashTable
{
    static constexpr  size_t default_buckets_size = 100;
    static constexpr  size_t grow_factor = 2;
    static constexpr  float max_load_factor = 0.8f;

    struct Entry
    {
        K key;
        V value;
    };

    Vector<List<Entry>> buckets;
    size_t _size;

  public:
    HashTable()
    {
        buckets = Vector<List<Entry>>(default_buckets_size);
        _size = 0;
    }

    HashTable(const HashTable &other)
    {
        buckets = other.buckets;
        _size = other._size;
    }

    HashTable(HashTable &&other) noexcept
    {
        buckets = std::move(other.buckets);
        _size = other._size;
    }

    HashTable &operator=(const HashTable &other)
    {
        if (&other == this) return *this;

        buckets = other.buckets;
        _size = other._size;

        return *this;
    }
    HashTable &operator=(HashTable &&other) noexcept
    {
        if (&other == this) return *this;

        buckets = std::move(other.buckets);
        _size = other._size;

        return *this;
    }

    ~HashTable() = default;

    V *get(const K &key)
    {
        size_t index = std::hash<K>{}(key) % buckets.size();

        for (int i = 0; i < buckets[index].size(); ++i)
        {
            if (buckets[index][i].key == key) { return &buckets[index][i].value; }
        }

        return nullptr;
    }

    /// Ajoute l'association (key, value) à la table.
    /// La fonction rend vrai si la valeur associée à key a été mise à jour dans la table,
    /// et faux si on a réalisé une insertion (la clé n'était pas encore dans la table).
    bool put(const K &key, const V &value)
    {
        size_t index = std::hash<K>{}(key) % buckets.size();

        for (int i = 0; i < buckets[index].size(); ++i)
        {
            if (buckets[index][i].key == key)
            {
                buckets[index][i].value = value;
                return true;
            }
        }

        if (_size > buckets.size() * max_load_factor) grow();
        index = std::hash<K>{}(key) % buckets.size();

        buckets[index].push_back({key, value});
        _size++;
        return false;
    }

    [[nodiscard]] size_t size() const { return _size; }

  private:
    void grow()
    {
        Vector<List<Entry>> new_buckets(buckets.size() * grow_factor);

        for (int i = 0; i < buckets.size(); ++i)
        {
            for (int j = 0; j < buckets[i].size(); ++j)
            {
                size_t index = std::hash<K>{}(buckets[i][j].key) % new_buckets.size();
                new_buckets[index].push_back(buckets[i][j]);
            }
        }

        buckets = std::move(new_buckets);
    }
};
} // namespace pscr
