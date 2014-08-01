find_package(GTest)

include_directories(${OLYMPUS_SOURCE_DIR}/inc)

link_directories (${OLYMPUS_BINARY_DIR}/src) 

add_executable(Tests olympus_test.cpp)

target_link_libraries(Tests Olympus)
target_link_libraries(Tests googletest)