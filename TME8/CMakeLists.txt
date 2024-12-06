cmake_minimum_required(VERSION 3.29)
project(tme8)

set(CMAKE_CXX_STANDARD 20)


add_executable(
        tme8_client
        src/Socket.cpp
        src/client.cpp
)

add_executable(
        tme8_server
        src/Socket.cpp
        src/server.cpp
        src/ServerSocket.cpp
)


add_custom_target(
        build_all
        DEPENDS tme8_client tme8_server
)

