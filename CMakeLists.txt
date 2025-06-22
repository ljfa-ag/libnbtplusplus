cmake_minimum_required(VERSION 3.26)
project(libnbt++
    VERSION 2.5)

# supported configure options
option(NBT_BUILD_SHARED "Build shared libraries" OFF)
option(NBT_USE_ZLIB "Build additional zlib stream functionality" ON)
option(NBT_BUILD_TESTS "Build the unit tests. Requires CxxTest." ON)

# hide this from includers.
set(BUILD_SHARED_LIBS ${NBT_BUILD_SHARED})

include(GenerateExportHeader)

set(NBT_SOURCES
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

set(NBT_SOURCES_Z
    src/io/izlibstream.cpp
    src/io/ozlibstream.cpp)

set(NBT_HEADERS
    include/crtp_tag.h
    include/endian_str.h
    include/make_unique.h
    include/nbt_tags.h
    include/nbt_visitor.h
    include/primitive_detail.h
    include/tag_array.h
    include/tag_compound.h
    include/tagfwd.h
    include/tag.h
    include/tag_list.h
    include/tag_primitive.h
    include/tag_string.h
    include/value.h
    include/value_initializer.h

    include/io/stream_reader.h
    include/io/stream_writer.h

    include/text/json_formatter.h)

set(NBT_HEADERS_Z
    include/io/izlibstream.h
    include/io/ozlibstream.h
    include/io/zlib_streambuf.h)

if(NBT_USE_ZLIB)
    find_package(ZLIB REQUIRED)
    list(APPEND NBT_SOURCES ${NBT_SOURCES_Z})
    list(APPEND NBT_HEADERS ${NBT_HEADERS_Z})
endif()

add_library(nbt++ ${NBT_SOURCES})
target_sources(nbt++ PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS include ${CMAKE_CURRENT_BINARY_DIR}
    FILES ${NBT_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/nbt_export.h) # install the headers as well as the generated export header
target_include_directories(nbt++ PUBLIC include ${CMAKE_CURRENT_BINARY_DIR})

if(NBT_USE_ZLIB)
    target_link_libraries(nbt++ ${ZLIB_LIBRARY})
    target_include_directories(nbt++ PUBLIC ${ZLIB_INCLUDE_DIRS})
    target_compile_definitions(nbt++ PUBLIC "-DNBT_HAVE_ZLIB")
endif()
set_property(TARGET nbt++ PROPERTY CXX_STANDARD 11)
generate_export_header(nbt++ BASE_NAME nbt)

if(${BUILD_SHARED_LIBS})
    set_target_properties(nbt++ PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()

install(TARGETS nbt++
    FILE_SET public_headers)

if(NBT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
