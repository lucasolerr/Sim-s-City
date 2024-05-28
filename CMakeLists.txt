cmake_minimum_required(VERSION 3.20)
project(ECECity C)
set(CMAKE_C_STANDARD 99)
# Projet principal
file(GLOB_RECURSE SOURCES "src/*.c")
include_directories("include")

# biblio graphique raylib
add_subdirectory("raylib")
include_directories("raylib")

add_executable(ECECity ${SOURCES})
target_link_libraries(ECECity raylib)

# ajouts des tests unitaires
add_subdirectory("tests")


