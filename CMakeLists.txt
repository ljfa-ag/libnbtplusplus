cmake_minimum_required(VERSION 3.0)
project(libnbt++
    VERSION 2.3)

include(GenerateExportHeader)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

find_package(ZLIB REQUIRED)

set(NBT_SOURCES
    src/endian_str.cpp
    src/tag.cpp
    src/tag_array.cpp
    src/tag_compound.cpp
    src/tag_list.cpp
    src/tag_string.cpp
    src/value.cpp
    src/value_initializer.cpp

    src/io/izlibstream.cpp
    src/io/ozlibstream.cpp
    src/io/stream_reader.cpp
    src/io/stream_writer.cpp

    src/text/json_formatter.cpp)

add_library(nbt++ ${NBT_SOURCES})
target_include_directories(nbt++ PUBLIC include ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(nbt++ z)
target_compile_options(nbt++ PUBLIC -std=c++11)
generate_export_header(nbt++ BASE_NAME nbt)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(NBT_BUILD_TESTS "Build the unit tests. Requires CxxTest." ON)

if(NBT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
