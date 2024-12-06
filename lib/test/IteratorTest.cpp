#include "HashTable.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

#include <gtest/gtest.h>

#include "List.hpp"
#include "Vector.hpp"

constexpr size_t testSize = 1000;

template <typename Iterator> void test_iterator(Iterator begin, Iterator end)
{
    EXPECT_NE(begin, end);

    std::vector<Iterator> iterators;
    iterators.reserve(testSize);

    for (auto it = begin; it != end; ++it)
    {
        iterators.push_back(it);
    }

    EXPECT_EQ(iterators.size(), testSize);

    for (size_t i = 0; i < iterators.size(); ++i)
    {
        for (size_t j = i + 1; j < iterators.size(); ++j)
        {
            EXPECT_FALSE(iterators[i] == iterators[j]);
            EXPECT_TRUE(iterators[i] != iterators[j]);
        }
    }
}

TEST(TestIterator, VectorIteratorTest)
{
    pscr::Vector<size_t> test_vector(testSize);

    for (size_t i = 0; i < test_vector.size(); ++i)
    {
        test_vector[i] = i;
    }

    test_iterator(test_vector.begin(), test_vector.end());
}

TEST(TestIterator, ListIteratorTest)
{
    pscr::List<size_t> test_list;

    for (size_t i = 0; i < testSize / 2; ++i)
    {
        test_list.push_back(i);
        test_list.push_front(i + i);
    }

    test_iterator(test_list.begin(), test_list.end());
}

TEST(TestIterator, HashTableIteratorTest)
{
    pscr::HashTable<std::string, std::string> test_hash_table;

    for (int i = 0; i < testSize; ++i)
    {
        test_hash_table.put(std::to_string(i*3-4+78+i*i), std::to_string(i));
    }

    test_iterator(test_hash_table.begin(), test_hash_table.end());
}
