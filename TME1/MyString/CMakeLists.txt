cmake_minimum_required(VERSION 3.29)
project(MyString)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyString main.cpp
        src/MyLib.cpp
        src/MyLib.hpp
        src/MyString.hpp
        src/MyString.cpp)
