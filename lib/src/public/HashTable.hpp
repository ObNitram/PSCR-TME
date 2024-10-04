#pragma once
#include "List.hpp"
#include "Vector.hpp"

#include <cstddef>
#include <functional>
#include <iostream>
#include <utility>

namespace pscr
{
template <typename K, typename V> class HashTable
{
    static constexpr size_t default_buckets_size = 100;
    static constexpr size_t grow_factor = 2;
    static constexpr float max_load_factor = 0.8f;

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

    class iterator
    {
        typename Vector<List<Entry>>::iterator _bucket_current;
        typename Vector<List<Entry>>::iterator _bucket_end;
        typename List<Entry>::iterator _list;

      public:
        iterator(typename Vector<List<Entry>>::iterator bucket_current,
                 typename Vector<List<Entry>>::iterator bucket_end)
            : _bucket_current(bucket_current), _bucket_end(bucket_end), _list(nullptr)
        {
            for (; _bucket_current != _bucket_end; ++_bucket_current)
            {
                if (!_bucket_current->isEmpty())
                {
                    _list = _bucket_current->begin();
                    return;
                }
            }
        }

        iterator &operator++()
        {
            if (_bucket_current == _bucket_end)
            {
                return *this;
            }

            ++_list;
            if (_list == _bucket_current->end())
            {
                ++_bucket_current;
                for (; _bucket_current != _bucket_end; ++_bucket_current)
                {
                    if (!_bucket_current->isEmpty())
                    {
                        _list = _bucket_current->begin();
                        return *this;
                    }
                }
                _list = typename List<Entry>::iterator(nullptr);
            }
            return *this;
        }

        bool operator==(const iterator &other) const
        {
            return _bucket_current == other._bucket_current && _list == other._list;
        }

        bool operator!=(const iterator &other) const { return !(_bucket_current == other._bucket_current); }

        std::pair<K, V> operator*() { return std::pair<K, V>((*_list).key, (*_list).value); }
    };

    class const_iterator
    {
        typename Vector<List<Entry>>::const_iterator _bucket_current;
        typename Vector<List<Entry>>::const_iterator _bucket_end;
        typename List<Entry>::const_iterator _list;

      public:
        const_iterator(typename Vector<List<Entry>>::const_iterator bucket_current,
                       typename Vector<List<Entry>>::const_iterator bucket_end)
            : _bucket_current(bucket_current), _bucket_end(bucket_end), _list(nullptr)
        {
            for (; _bucket_current != _bucket_end; ++_bucket_current)
            {
                if (!_bucket_current->isEmpty())
                {
                    _list = std::as_const(*_bucket_current).begin();
                    return;
                }
            }
        }

        explicit const_iterator(typename Vector<List<Entry>>::iterator other)
            : _bucket_current(other.bucket_current), _bucket_end(other.bucket_end), _list(nullptr)
        {
        }

        const_iterator &operator++()
        {
            if (_bucket_current == _bucket_end)
            {
                return *this;
            }

            ++_list;
            if (_list == std::as_const(*_bucket_current).end())
            {
                ++_bucket_current;

                for (; _bucket_current != _bucket_end; ++_bucket_current)
                {
                    if (!_bucket_current->isEmpty())
                    {
                        _list = std::as_const(*_bucket_current).begin();
                        return *this;
                    }
                }
                _list = typename List<Entry>::const_iterator(nullptr);
            }
            return *this;
        }

        bool operator==(const const_iterator &other) const
        {
            return _bucket_current == other._bucket_current && _list == other._list;
        }

        bool operator!=(const const_iterator &other) const { return !(*this == other); }

        std::pair<K, V> operator*() const { return std::pair<K, V>((*_list).key, (*_list).value); }
    };

    iterator begin() { return iterator(buckets.begin(), buckets.end()); }
    iterator end() { return iterator(buckets.end(), buckets.end()); }

    const_iterator begin() const { return const_iterator(buckets.begin(), buckets.end()); }
    const_iterator end() const { return const_iterator(buckets.end(), buckets.end()); }

    V *get(const K &key)
    {
        size_t index = std::hash<K>{}(key) % buckets.size();

        for (int i = 0; i < buckets[index].size(); ++i)
        {
            if (buckets[index][i].key == key)
            {
                return &buckets[index][i].value;
            }
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
