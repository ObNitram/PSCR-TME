cmake_minimum_required(VERSION 3.29)
project(TME2)

set(CMAKE_CXX_STANDARD 20)

# Ajouter la bibliothèque via add_subdirectory
add_subdirectory("/home/obnitram/Projects/cours/pscr/PSCR-TME/lib" "${CMAKE_BINARY_DIR}/lib_build")

# Inclure les fichiers d'en-tête de la bibliothèque
include_directories("/home/obnitram/Projects/cours/pscr/PSCR-TME/lib/src/public")


# Créer l'exécutable principal
add_executable(MyApp main.cpp)

# Lier l'exécutable avec la bibliothèque PscrLib
target_link_libraries(MyApp PRIVATE PscrLib)