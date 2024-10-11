#include "Vector.hpp"
#include <gtest/gtest.h>

using namespace pscr;

// Test pour vérifier l'initialisation par défaut
TEST(VectorTest, DefaultConstructor)
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_TRUE(v.isEmpty());
}

// Test pour vérifier la création avec une taille initiale
TEST(VectorTest, ConstructorWithSize)
{
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_FALSE(v.isEmpty());
}

// Test pour vérifier l'ajout d'éléments avec `push_back`
TEST(VectorTest, PushBack)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

// Test pour vérifier l'accès par l'opérateur d'indexation
TEST(VectorTest, IndexOperator)
{
    Vector<int> v(3);
    v.push_back(10);
    v[0] = 20;
    EXPECT_EQ(v[0], 20); // Puisqu'il n'y a pas de valeurs assignées
}

// Test pour vérifier que l'accès constant par l'opérateur d'indexation fonctionne
TEST(VectorTest, ConstIndexOperator)
{
    Vector<int> v(2);
    const Vector<int> &const_v = v;
    v.push_back(30);
    EXPECT_EQ(const_v[2], 30);
}

// Test pour vérifier la copie
TEST(VectorTest, CopyConstructor)
{
    Vector<int> v;
    v.push_back(42);
    Vector<int> v_copy(v);
    EXPECT_EQ(v_copy.size(), v.size());
    EXPECT_EQ(v_copy[0], 42);
}

// Test pour vérifier l'opérateur de copie
TEST(VectorTest, CopyAssignment)
{
    Vector<int> v;
    v.push_back(100);
    Vector<int> v_copy;
    v_copy = v;
    EXPECT_EQ(v_copy.size(), v.size());
    EXPECT_EQ(v_copy[0], 100);
}

// Test pour vérifier le constructeur par déplacement
TEST(VectorTest, MoveConstructor)
{
    Vector<int> v;
    v.push_back(50);
    Vector<int> v_moved(std::move(v));
    EXPECT_EQ(v_moved.size(), 1);
}

// Test pour vérifier l'opérateur de déplacement
TEST(VectorTest, MoveAssignment)
{
    Vector<int> v;
    v.push_back(60);
    Vector<int> v_moved;
    v_moved = std::move(v);
    EXPECT_EQ(v_moved.size(), 1);
    EXPECT_EQ(v_moved[0], 60);
}

// Test pour vérifier l'augmentation de capacité
TEST(VectorTest, EnsureCapacity)
{
    Vector<int> v(2);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3); // Devrait déclencher une réallocation
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v[4], 3);
}

// Tests pour vérifier les itérateurs
TEST(VectorTest, IteratorBeginEnd)
{
    auto v = Vector<int>(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    auto it = v.begin();
    EXPECT_EQ(*it, 1); // Vérifie que l'itérateur commence au début

    ++it;
    EXPECT_EQ(*it, 2); // Vérifie que l'itérateur avance correctement

    ++it;
    EXPECT_EQ(*it, 3); // Vérifie qu'on atteint le dernier élément

    ++it;
    EXPECT_EQ(it, v.end()); // Vérifie que l'itérateur atteint la fin
}

TEST(VectorTest, ConstIterator)
{
    auto v = Vector<int>(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;

    const Vector<int> &const_v = v;
    auto it = const_v.begin();
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(VectorTest, ForEachLoop)
{
    auto v = Vector<int>(3);
    v[0] = 10;
    v[1] = 20;
    v[2] = 30;

    constexpr  int expected_values[] = {10, 20, 30};
    int index = 0;
    for (int& value : v)
    {
        EXPECT_EQ(value, expected_values[index++]);
    }
}

TEST(VectorTest, ForEachLoopConst)
{
    auto v = Vector<int>(3);
    v[0] = 10;
    v[1] = 20;
    v[2] = 30;

    constexpr int expected_values[] = {10, 20, 30};
    int index = 0;
    for (const auto& value : v)
    {
        EXPECT_EQ(value, expected_values[index++]);
    }
}

TEST(VectorTest, IteratorComparison)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    auto it1 = v.begin();
    auto it2 = v.begin();
    EXPECT_EQ(it1, it2); // Les itérateurs devraient être égaux au début

    ++it2;
    EXPECT_NE(it1, it2); // Après incrémentation, ils devraient être différents
}

TEST(VectorTest, IteratorManualLoop)
{
    auto v = Vector<int>(3);
    v[0] = 5;
    v[1] = 10;
    v[2] = 15;

    auto it = v.begin();
    EXPECT_EQ(*it, 5);

    ++it;
    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 15);

    ++it;
    EXPECT_EQ(it, v.end()); // Vérifie qu'on atteint la fin
}