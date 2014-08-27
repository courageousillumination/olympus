include_directories(${OLYMPUS_SOURCE_DIR}/inc)

FILE(GLOB sources "*/*.cpp")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

add_library(Olympus ${sources})