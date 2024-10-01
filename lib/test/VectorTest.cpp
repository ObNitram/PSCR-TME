#include "Vector.hpp"
#include <gtest/gtest.h>

using namespace pscr;

// Test pour vérifier l'initialisation par défaut
TEST(VectorTest, DefaultConstructor)
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 10);
    EXPECT_FALSE(v.isEmpty());
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
    EXPECT_EQ(v.size(), 12);
    EXPECT_EQ(v[10], 1);
    EXPECT_EQ(v[11], 2);
}

// Test pour vérifier l'accès par l'opérateur d'indexation
TEST(VectorTest, IndexOperator)
{
    Vector<int> v(3);
    v.push_back(10);
    v[0] = 20;
    EXPECT_EQ(v[0], 20);// Puisqu'il n'y a pas de valeurs assignées
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
    EXPECT_EQ(v_copy[10], 42);
}

// Test pour vérifier l'opérateur de copie
TEST(VectorTest, CopyAssignment)
{
    Vector<int> v;
    v.push_back(100);
    Vector<int> v_copy;
    v_copy = v;
    EXPECT_EQ(v_copy.size(), v.size());
    EXPECT_EQ(v_copy[10], 100);
}

// Test pour vérifier le constructeur par déplacement
TEST(VectorTest, MoveConstructor)
{
    Vector<int> v;
    v.push_back(50);
    Vector<int> v_moved(std::move(v));
    EXPECT_EQ(v_moved.size(), 11);
}

// Test pour vérifier l'opérateur de déplacement
TEST(VectorTest, MoveAssignment)
{
    Vector<int> v;
    v.push_back(60);
    Vector<int> v_moved;
    v_moved = std::move(v);
    EXPECT_EQ(v_moved.size(), 11);
    EXPECT_EQ(v_moved[10], 60);
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
