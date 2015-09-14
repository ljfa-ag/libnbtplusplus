cmake_minimum_required(VERSION 3.0)
project(libnbt++
    VERSION 2.1)

add_definitions(-std=c++11)
include_directories(include)
add_library(nbt++ STATIC
    src/endian_str.cpp
    src/tag.cpp
    src/tag_array.cpp
    src/tag_compound.cpp
    src/tag_list.cpp
    src/tag_string.cpp
    src/value.cpp
    src/value_initializer.cpp

    src/io/stream_reader.cpp
    src/io/stream_writer.cpp

    src/text/json_formatter.cpp)

find_package(zlib REQUIRED)
find_package(CxxTest)

option(NBT_BUILD_TESTS "Build the unit tests. Requires CxxTest." ${CXXTEST_FOUND})

if(NBT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
