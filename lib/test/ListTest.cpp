#include <gtest/gtest.h>
#include "List.hpp" // Remplace par le bon chemin

using namespace pscr;

// Test du constructeur par défaut
TEST(ListTest, DefaultConstructor) {
    List<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

// Test de `push_back`
TEST(ListTest, PushBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

// Test de `push_front`
TEST(ListTest, PushFront) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], 3);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 1);
}

// Test pour `operator[]` (accès à l'index)
TEST(ListTest, IndexOperator) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_EQ(list[0], 10);
    EXPECT_EQ(list[1], 20);
    EXPECT_EQ(list[2], 30);

    list[1] = 100;  // Modification via l'opérateur
    EXPECT_EQ(list[1], 100);
}

// Test pour vérifier la copie de la liste
TEST(ListTest, CopyConstructor) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int> copy(list); // Copie via constructeur
    EXPECT_EQ(copy.size(), list.size());
    EXPECT_EQ(copy[0], list[0]);
    EXPECT_EQ(copy[1], list[1]);
    EXPECT_EQ(copy[2], list[2]);
}

// Test pour vérifier l'affectation par copie
TEST(ListTest, CopyAssignment) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int> copy;
    copy = list; // Affectation par copie
    EXPECT_EQ(copy.size(), list.size());
    EXPECT_EQ(copy[0], list[0]);
    EXPECT_EQ(copy[1], list[1]);
    EXPECT_EQ(copy[2], list[2]);
}

// Test pour vérifier le constructeur par déplacement
TEST(ListTest, MoveConstructor) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    List<int> movedList(std::move(list)); // Déplacement
    EXPECT_EQ(movedList.size(), 2);
    EXPECT_EQ(movedList[0], 1);
    EXPECT_EQ(movedList[1], 2);
    EXPECT_EQ(list.size(), 0); // Liste déplacée est vide
    EXPECT_TRUE(list.isEmpty());
}

// Test pour vérifier l'affectation par déplacement
TEST(ListTest, MoveAssignment) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    List<int> movedList;
    movedList = std::move(list); // Affectation par déplacement
    EXPECT_EQ(movedList.size(), 2);
    EXPECT_EQ(movedList[0], 1);
    EXPECT_EQ(movedList[1], 2);
}

// Test de `size`
TEST(ListTest, Size) {
    List<int> list;
    EXPECT_EQ(list.size(), 0);

    list.push_back(1);
    EXPECT_EQ(list.size(), 1);

    list.push_front(2);
    EXPECT_EQ(list.size(), 2);
}

// Test pour vérifier si la liste est vide
TEST(ListTest, IsEmpty) {
    List<int> list;
    EXPECT_TRUE(list.isEmpty());

    list.push_back(1);
    EXPECT_FALSE(list.isEmpty());
}

// Test pour vérifier les limites d'accès avec l'assert
TEST(ListTest, OutOfBoundsAccess) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    EXPECT_DEATH(list[2], ".*");  // Teste un accès hors limites
}

