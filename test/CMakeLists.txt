find_package(GTest)

include_directories(${OLYMPUS_SOURCE_DIR}/inc)

link_directories (${OLYMPUS_BINARY_DIR}/src) 

FILE(GLOB tests "*_test.cpp")

add_executable(Tests ${tests})

target_link_libraries(Tests Olympus)
target_link_libraries(Tests googletest)