include_directories(${OLYMPUS_SOURCE_DIR}/inc)

FILE(GLOB sources "*/*.cpp")

add_library(Olympus ${sources})