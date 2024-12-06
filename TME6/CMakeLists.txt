cmake_minimum_required(VERSION 3.5.0)
project(tme6 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(tme6_fork src/fork_exo.cpp)

add_executable(star_wars
        src/main.cpp src/rsleep.cpp)

