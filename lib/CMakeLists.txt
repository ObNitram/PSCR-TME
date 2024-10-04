cmake_minimum_required(VERSION 3.29)
project(PscrLib)

set(CMAKE_CXX_STANDARD 20)


# Créer la bibliothèque statique en utilisant les fichiers sources
add_library(PscrLib STATIC
        src/private/HashTable.cpp src/public/HashTable.hpp
        src/private/List.cpp src/public/List.hpp
        src/private/String.cpp src/public/String.hpp
        src/private/Vector.cpp src/public/Vector.hpp
        src/private/Core.cpp src/public/Core.hpp
)

# Spécifier les répertoires d'inclusion après la création de la bibliothèque
target_include_directories(PscrLib PUBLIC ${CMAKE_SOURCE_DIR}/src/public)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip
)

FetchContent_MakeAvailable(googletest)


# Activer le support des tests
enable_testing()

# Ajouter les tests
add_executable(PscrLibTests
        test/StringTest.cpp
        test/VectorTest.cpp
        test/ListTest.cpp
        test/HashTableTest.cpp
        test/CoreTest.cpp
)

# Lier les tests avec Google Test et la bibliothèque PscrLib
target_link_libraries(PscrLibTests
        GTest::gtest_main  # Liaison avec GoogleTest
        PscrLib            # Liaison avec ta bibliothèque
)

# Ajouter un test CTest pour exécuter les tests
add_test(NAME PscrLibTests COMMAND PscrLibTests)
