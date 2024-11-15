cmake_minimum_required(VERSION 3.29)
project(tme7)

set(CMAKE_CXX_STANDARD 20)

# Collecter tous les fichiers .cpp et .hh
file(GLOB_RECURSE LIB_PUBLIC_HEADERS "src/lib/public/*.hh")
file(GLOB_RECURSE LIB_PRIVATE_SOURCES "src/lib/private/*.cpp")

# Ajouter les fichiers au projet
add_executable(
        tme7 ./src/prod_cons.cpp
        ${LIB_PUBLIC_HEADERS} ${LIB_PRIVATE_SOURCES}
        ./src/Stack.h
)

# Optionnel : si vous avez besoin de définir des dossiers d'inclusion pour les headers
target_include_directories(tme7 PUBLIC src/lib/public)
