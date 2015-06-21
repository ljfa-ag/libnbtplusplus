enable_testing()
include_directories(${libnbt++_SOURCE_DIR}/include)

add_executable(nbttest nbttest.cpp)
target_link_libraries(nbttest nbt++)
add_test(nbttest nbttest)
