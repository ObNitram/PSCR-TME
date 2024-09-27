cmake_minimum_required(VERSION 3.29)
project(Tpe2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

add_executable(Tpe2 main.cpp
        src/HashMap.hpp
        ../../lib/String.cpp
        ../../lib/String.hpp)
