cmake_minimum_required(VERSION 2.6)
project(libnbt++)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

option(NBT_WITH_GZIP "Build with GZip support. Requires Boost.Iostreams with Zlib support." ON)
option(NBT_BUILD_NBTTEST "Build the nbttest example program. Requires GZip support." ${NBT_WITH_GZIP})

if(NBT_WITH_GZIP)
    find_package(Boost COMPONENTS iostreams REQUIRED)
endif()

if(NBT_BUILD_NBTTEST AND NOT NBT_WITH_GZIP)
    message(FATAL_ERROR "nbttest requires libnbt++ to have GZip support!")
endif()

configure_file("include/nbt_conf.h.in" "${PROJECT_BINARY_DIR}/config/nbt_conf.h")

include_directories(include)
include_directories("${PROJECT_BINARY_DIR}/config")

add_definitions(-std=c++11)
add_library(nbt++ STATIC src/endian_str.cpp src/read.cpp src/tag.cpp src/tag_array.cpp src/tag_compound.cpp src/tag_list.cpp)
install(TARGETS nbt++ DESTINATION lib)
install(FILES
    "${PROJECT_BINARY_DIR}/config/nbt_conf.h"
    include/endian_str.h
    include/nbt_io.h
    include/tag.h
    include/tag_base.h
    include/tag_byte_array.h
    include/tag_compound.h
    include/tag_int_array.h
    include/tag_list.h
    include/tag_scalar.h
    include/tag_string.h
DESTINATION include/NBT)

if(NBT_BUILD_NBTTEST)
    add_executable(nbttest test.cpp)
    target_link_libraries(nbttest nbt++ ${Boost_LIBRARIES})
endif()