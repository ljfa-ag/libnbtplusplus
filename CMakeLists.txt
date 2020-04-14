cmake_minimum_required(VERSION 3.16)
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

if(NBT_USE_ZLIB)
    find_package(ZLIB REQUIRED)
    list(APPEND NBT_SOURCES ${NBT_SOURCES_Z})
endif()

add_library(nbt++ ${NBT_SOURCES})
target_include_directories(nbt++ PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/libnbt++>")

target_include_directories(nbt++ PUBLIC
        "$<INSTALL_INTERFACE:include>")

if(NBT_USE_ZLIB)
    target_link_libraries(nbt++ ${ZLIB_LIBRARY})
    target_include_directories(nbt++ PUBLIC ${ZLIB_INCLUDE_DIRS})
    target_compile_definitions(nbt++ PUBLIC "-DNBT_HAVE_ZLIB")
endif()
target_compile_options(nbt++ PUBLIC -std=c++11)
generate_export_header(nbt++ BASE_NAME nbt)

if(${BUILD_SHARED_LIBS})
    set_target_properties(nbt++ PROPERTIES
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN 1)
endif()

if(NBT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()


#
# installation
#

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")
set(lib_install_dir "lib")
set(pkgconfig_install_dir "lib/pkgconfig")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(pkg_config "${generated_dir}/${PROJECT_NAME}.pc")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "libnbt++::")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${version_config}" COMPATIBILITY SameMajorVersion
)

configure_file("cmake/libnbt++.pc.in" "${pkg_config}" @ONLY)

configure_package_config_file(
        "cmake/Config.cmake.in"
        "${project_config}"
        INSTALL_DESTINATION "${config_install_dir}"
)

install(TARGETS nbt++
        EXPORT "${targets_export_name}"
        INCLUDES DESTINATION "${include_install_dir}"
        ARCHIVE DESTINATION "${lib_install_dir}")

install(DIRECTORY include/libnbt++ DESTINATION "${include_install_dir}")

install(
        FILES "${project_config}" "${version_config}"
        DESTINATION "${config_install_dir}"
)

install(
        FILES "${pkg_config}"
        DESTINATION "${pkgconfig_install_dir}"
)

install(
        EXPORT "${targets_export_name}"
        NAMESPACE "${namespace}"
        DESTINATION "${config_install_dir}"
)
