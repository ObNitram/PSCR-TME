#include "Core.hpp" // Remplacer par le chemin correct
#include <gtest/gtest.h>

using namespace pscr;

// Tests pour la fonction count
TEST(CountTest, EmptyVector) {
    std::vector<int> vec;
    EXPECT_EQ(Core::count(vec.begin(), vec.end()), 0);
}

TEST(CountTest, NonEmptyVector) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_EQ(Core::count(vec.begin(), vec.end()), 5);
}

// Tests pour la fonction count_if_equal
TEST(CountIfEqualTest, NoMatchingElements) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    EXPECT_EQ(Core::count_if_equal(vec.begin(), vec.end(), 6), 0);
}

TEST(CountIfEqualTest, SomeMatchingElements) {
    std::vector<int> vec = {1, 2, 3, 2, 5, 2};
    EXPECT_EQ(Core::count_if_equal(vec.begin(), vec.end(), 2), 3);
}

TEST(CountIfEqualTest, AllMatchingElements) {
    std::vector<int> vec = {1, 1, 1, 1};
    EXPECT_EQ(Core::count_if_equal(vec.begin(), vec.end(), 1), 4);
}

TEST(CountIfEqualTest, MixedDataTypes) {
    std::vector<double> vec = {1.1, 2.2, 3.3, 2.2, 5.5};
    EXPECT_EQ(Core::count_if_equal(vec.begin(), vec.end(), 2.2), 2);
}

