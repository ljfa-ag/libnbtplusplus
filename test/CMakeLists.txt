enable_testing()
include_directories(${libnbt++_SOURCE_DIR}/include)

add_executable(nbttest nbttest.cpp)
target_link_libraries(nbttest nbt++)
add_test(nbttest nbttest)

add_executable(endian_str_test endian_str_test.cpp)
target_link_libraries(endian_str_test nbt++)
add_test(endian_str_test endian_str_test)
