#include "../public/String.hpp"
#include <gtest/gtest.h>
#include <sstream>

namespace pscr
{

class StringTest : public ::testing::Test
{
  protected:
    // Setup commun pour chaque test (s'il est nécessaire)
    void SetUp() override {}

    // Nettoyage après chaque test (si nécessaire)
    void TearDown() override {}
};

// Test du constructeur de base
TEST_F(StringTest, Constructor)
{
    const char *testStr = "Hello";
    String myString(testStr);

    std::stringstream ss;
    ss << myString;

    EXPECT_EQ(ss.str(), "Hello");
}

// Test du constructeur par copie
TEST_F(StringTest, CopyConstructor)
{
    const char *testStr = "CopyMe";
    String original(testStr);
    String copy = original;

    std::stringstream ss;
    ss << copy;

    EXPECT_EQ(ss.str(), "CopyMe");
    EXPECT_NE(&original, &copy); // Les deux objets doivent être différents
}

// Test du constructeur par déplacement
TEST_F(StringTest, MoveConstructor)
{
    const char *testStr = "MoveMe";
    String original(testStr);
    String moved = std::move(original);

    std::stringstream ss;
    ss << moved;

    EXPECT_EQ(ss.str(), "MoveMe");
}

// Test de l'opérateur d'affectation par copie
TEST_F(StringTest, CopyAssignment)
{
    const char *testStr = "CopyAssign";
    String original(testStr);
    String copy("Temporary");
    copy = original;

    std::stringstream ss;
    ss << copy;

    EXPECT_EQ(ss.str(), "CopyAssign");
}

// Test de l'opérateur d'affectation par déplacement
TEST_F(StringTest, MoveAssignment)
{
    const char *testStr = "MoveAssign";
    String original(testStr);
    String moved("Temporary");
    moved = std::move(original);

    std::stringstream ss;
    ss << moved;

    EXPECT_EQ(ss.str(), "MoveAssign");
}

// Test du destructeur
TEST_F(StringTest, Destructor)
{
    const char *testStr = "DestructMe";
    auto *dynamicString = new String(testStr);
    delete dynamicString; // Test du destructeur, pas d'assertions à faire ici

    // Assurer qu'aucun crash ne survient, pas de tests explicites ici
}

// Test de l'opérateur de flux <<
TEST_F(StringTest, StreamOperator)
{
    const char *testStr = "StreamTest";
    String myString(testStr);

    std::stringstream ss;
    ss << myString;

    EXPECT_EQ(ss.str(), "StreamTest");
}

} // namespace pscr
