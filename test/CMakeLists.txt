enable_testing()
include_directories(${libnbt++_SOURCE_DIR}/include)
include_directories(${CXXTEST_INCLUDE_DIR})

CXXTEST_ADD_TEST(nbttest nbttest.cpp ${CMAKE_CURRENT_SOURCE_DIR}/nbttest.h)
target_link_libraries(nbttest nbt++)

add_executable(endian_str_test endian_str_test.cpp)
target_link_libraries(endian_str_test nbt++)
add_test(endian_str_test endian_str_test)

add_executable(read_test read_test.cpp)
target_link_libraries(read_test nbt++)
add_custom_command(TARGET read_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/testfiles ${CMAKE_CURRENT_BINARY_DIR})
add_test(read_test read_test)

add_executable(write_test write_test.cpp)
target_link_libraries(write_test nbt++)
add_test(write_test write_test)

add_executable(format_test format_test.cpp)
target_link_libraries(format_test nbt++)
add_test(format_test format_test)
