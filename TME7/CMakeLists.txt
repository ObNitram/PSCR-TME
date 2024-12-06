cmake_minimum_required(VERSION 3.29)
project(tme7)

set(CMAKE_CXX_STANDARD 20)


add_executable(
        tme7_pipe
        ./src/pipe/pipe.cpp
)

add_executable(
        tme7_prod_cons
        ./src/prod_cons/prod_cons.cpp
)

add_custom_target(
        build_all
        DEPENDS tme7_pipe tme7_prod_cons
)

