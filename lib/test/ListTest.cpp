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

// Tests pour les itérateurs de `List`
TEST(ListTest, IteratorBeginEnd) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    EXPECT_EQ(*it, 1); // Vérifie que l'itérateur commence au premier élément

    ++it;
    EXPECT_EQ(*it, 2); // Vérifie que l'itérateur avance correctement

    ++it;
    EXPECT_EQ(*it, 3); // Vérifie qu'on atteint le dernier élément

    ++it;
    EXPECT_EQ(it, list.end()); // Vérifie que l'itérateur atteint la fin
}

TEST(ListTest, ConstIterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    const List<int>& const_list = list;
    auto it = const_list.begin();
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(ListTest, ForEachLoop) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int expected_values[] = {10, 20, 30};
    int index = 0;
    for (int value : list) {
        EXPECT_EQ(value, expected_values[index++]);
    }
}

TEST(ListTest, IteratorComparison) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it1 = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it1, it2); // Les itérateurs devraient être égaux au début

    ++it2;
    EXPECT_NE(it1, it2); // Après incrémentation, ils devraient être différents
}

TEST(ListTest, IteratorManualLoop) {
    List<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    auto it = list.begin();
    EXPECT_EQ(*it, 5);

    ++it;
    EXPECT_EQ(*it, 10);

    ++it;
    EXPECT_EQ(*it, 15);

    ++it;
    EXPECT_EQ(it, list.end()); // Vérifie qu'on atteint la fin
}
