#pragma once
#include <cstddef>

namespace pscr
{
template <typename K, typename V> class HashTable
{
  public:
    HashTable();

    HashTable(const HashTable &other);
    HashTable(HashTable &&other);

    HashTable &operator=(const HashTable &other);
    HashTable &operator=(HashTable &&other);

    ~HashTable();

    V *get(const K &key);

    bool put(const K &key, const V &value);

    size_t size() const;
};
} // namespace pscr
