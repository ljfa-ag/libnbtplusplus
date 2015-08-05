enable_testing()
include_directories(.)
include_directories(${libnbt++_SOURCE_DIR}/include)

add_executable(nbttest nbttest.cpp)
target_link_libraries(nbttest nbt++)
add_test(nbttest nbttest)

add_executable(endian_str_test endian_str_test.cpp)
target_link_libraries(endian_str_test nbt++)
add_test(endian_str_test endian_str_test)

add_executable(read_test io/read_test.cpp)
target_link_libraries(read_test nbt++)
add_custom_command(TARGET read_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
    copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/io/bigtest.nbt ${CMAKE_CURRENT_BINARY_DIR})
add_test(read_test read_test)
