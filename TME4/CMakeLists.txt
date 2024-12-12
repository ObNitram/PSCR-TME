cmake_minimum_required(VERSION 3.29)
project(tme4)

set(CMAKE_CXX_STANDARD 20)

# Créer l'exécutable principal
add_executable(tme4 ./src/main.cpp
        src/Compte.cpp
        src/Banque.cpp)


