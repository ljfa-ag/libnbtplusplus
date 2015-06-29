cmake_minimum_required(VERSION 2.6)
project(libnbt++)
set(libnbt++_VERSION_MAJOR 2)
set(libnbt++_VERSION_MINOR 0)

add_definitions(-std=c++11)
include_directories(include)
add_library(nbt++ STATIC
    src/tag_string.cpp)

enable_testing()
add_subdirectory(test)
