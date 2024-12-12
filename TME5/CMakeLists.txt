cmake_minimum_required(VERSION 3.25)
project(tme5)

set(CMAKE_CXX_STANDARD 20)

# Collecter tous les fichiers .cpp et .hh
file(GLOB_RECURSE LIB_PUBLIC_HEADERS "src/lib/public/*.hh")
file(GLOB_RECURSE LIB_PRIVATE_SOURCES "src/lib/private/*.cpp")


# Ajouter les fichiers au projet
add_executable(tme5 ./src/main.cpp ${LIB_PUBLIC_HEADERS} ${LIB_PRIVATE_SOURCES}
        src/lib/public/Vec3D.hpp
        src/lib/public/Pool.hpp
        src/lib/public/Utils.hpp)

target_include_directories(tme5 PUBLIC src/lib/public)
