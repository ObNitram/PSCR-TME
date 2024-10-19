cmake_minimum_required(VERSION 3.29)
project(tme5)

set(CMAKE_CXX_STANDARD 20)

# Créer l'exécutable principal
add_executable(tme5 ./src/main.cpp
        src/Color.cpp
        src/Vec3D.cpp
        src/Pool.h)
