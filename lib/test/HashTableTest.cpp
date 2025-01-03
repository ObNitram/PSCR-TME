#include "HashTable.hpp" // Remplacer par le chemin correct
#include <gtest/gtest.h>

using namespace pscr;

// Test du constructeur par défaut
TEST(HashTableTest, DefaultConstructor)
{
    HashTable<int, std::string> table;
    EXPECT_EQ(table.size(), 0);
}

// Test de `put` avec insertion de nouvelles clés
TEST(HashTableTest, PutInsertion)
{
    HashTable<int, std::string> table;
    EXPECT_FALSE(table.put(1, "one")); // Nouvelle insertion
    EXPECT_FALSE(table.put(2, "two")); // Nouvelle insertion
    EXPECT_EQ(table.size(), 2);        // Taille doit être 2
}

// Test de `put` avec mise à jour de la valeur d'une clé existante
TEST(HashTableTest, PutUpdate)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    EXPECT_TRUE(table.put(1, "uno")); // Mise à jour de la valeur
    EXPECT_EQ(*table.get(1), "uno");  // Vérifie la mise à jour
    EXPECT_EQ(table.size(), 1);       // Taille ne change pas
}

// Test de `get` avec une clé existante
TEST(HashTableTest, GetExistingKey)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");
    EXPECT_NE(table.get(1), nullptr);
    EXPECT_EQ(*table.get(1), "one");
    EXPECT_NE(table.get(2), nullptr);
    EXPECT_EQ(*table.get(2), "two");
}

// Test de `get` avec une clé inexistante
TEST(HashTableTest, GetNonExistingKey)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    EXPECT_EQ(table.get(100), nullptr); // Clé non présente
}

// Test pour vérifier les collisions (chaînage)
TEST(HashTableTest, HandleCollisions)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(1001, "one thousand and one");

    EXPECT_EQ(table.size(), 2);
    EXPECT_NE(table.get(1), nullptr);
    EXPECT_EQ(*table.get(1), "one");
    EXPECT_NE(table.get(1001), nullptr);
    EXPECT_EQ(*table.get(1001), "one thousand and one");
}

// Test du constructeur par copie
TEST(HashTableTest, CopyConstructor)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");

    HashTable<int, std::string> copy(table); // Copie de la table
    EXPECT_EQ(copy.size(), table.size());
    EXPECT_NE(copy.get(1), nullptr);
    EXPECT_EQ(*copy.get(1), "one");
    EXPECT_NE(copy.get(2), nullptr);
    EXPECT_EQ(*copy.get(2), "two");
}

// Test de l'affectation par copie
TEST(HashTableTest, CopyAssignment)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");

    HashTable<int, std::string> copy;
    copy = table; // Affectation par copie
    EXPECT_EQ(copy.size(), table.size());
    EXPECT_NE(copy.get(1), nullptr);
    EXPECT_EQ(*copy.get(1), "one");
    EXPECT_NE(copy.get(2), nullptr);
    EXPECT_EQ(*copy.get(2), "two");
}

// Test du constructeur par déplacement
TEST(HashTableTest, MoveConstructor)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");

    HashTable<int, std::string> movedTable(std::move(table)); // Déplacement
    EXPECT_EQ(movedTable.size(), 2);
    EXPECT_EQ(*movedTable.get(1), "one");
    EXPECT_EQ(*movedTable.get(2), "two");
}

// Test de l'affectation par déplacement
TEST(HashTableTest, MoveAssignment)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");

    HashTable<int, std::string> movedTable;
    movedTable = std::move(table); // Affectation par déplacement
    EXPECT_EQ(movedTable.size(), 2);
    EXPECT_EQ(*movedTable.get(1), "one");
    EXPECT_EQ(*movedTable.get(2), "two");
}

// Test pour vérifier la croissance (fonction grow) si nécessaire
TEST(HashTableTest, GrowTest)
{
    HashTable<int, std::string> table;
    // Simule un remplissage complet qui déclenche une croissance
    for (int i = 0; i < 10000; ++i)
    {
        table.put(i, "value" + std::to_string(i));
        EXPECT_EQ(table.size(), i + 1);
        EXPECT_EQ(*table.get(i), "value" + std::to_string(i));
        EXPECT_EQ(table.get(i + 1), nullptr);
    }
}
// Tests pour les itérateurs de `HashTable`
TEST(HashTableTest, IteratorBeginEnd)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");
    table.put(3, "three");

    auto it = table.begin();
    EXPECT_EQ((*it).first, 1);
    EXPECT_EQ((*it).second, "one");

    ++it;
    EXPECT_EQ((*it).first, 2);
    EXPECT_EQ((*it).second, "two");

    ++it;
    EXPECT_EQ((*it).first, 3);
    EXPECT_EQ((*it).second, "three");

    ++it;
    EXPECT_EQ(it, table.end()); // Vérifie que l'itérateur atteint la fin
}

TEST(HashTableTest, ConstIterator)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");
    table.put(3, "three");

    const HashTable<int, std::string> &const_table = table;
    auto it = const_table.begin();
    EXPECT_EQ((*it).first, 1);
    EXPECT_EQ((*it).second, "one");

    ++it;
    EXPECT_EQ((*it).first, 2);
    EXPECT_EQ((*it).second, "two");

    ++it;
    EXPECT_EQ((*it).first, 3);
    EXPECT_EQ((*it).second, "three");
}

TEST(HashTableTest, ForEachLoop)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");
    table.put(3, "three");

    std::unordered_map<int, std::string> expected_values = {{1, "one"}, {2, "two"}, {3, "three"}};
    for (const auto &[key, value] : table)
    {
        EXPECT_EQ(expected_values[key], value);
    }
}

TEST(HashTableTest, IteratorComparison)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");

    auto it1 = table.begin();
    auto it2 = table.begin();
    EXPECT_EQ(it1, it2); // Les itérateurs devraient être égaux au début

    ++it2;
    EXPECT_NE(it1, it2); // Après incrémentation, ils devraient être différents
}

TEST(HashTableTest, IteratorManualLoop)
{
    HashTable<int, std::string> table;
    table.put(1, "one");
    table.put(2, "two");
    table.put(3, "three");

    auto it = table.begin();
    EXPECT_EQ((*it).first, 1);
    EXPECT_EQ((*it).second, "one");

    ++it;
    EXPECT_EQ((*it).first, 2);
    EXPECT_EQ((*it).second, "two");

    ++it;
    EXPECT_EQ((*it).first, 3);
    EXPECT_EQ((*it).second, "three");

    ++it;
    EXPECT_EQ(it, table.end()); // Vérifie qu'on atteint la fin
}
