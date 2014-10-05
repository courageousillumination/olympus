include_directories(${OLYMPUS_SOURCE_DIR}/inc /usr/include/freetype2)

FILE(GLOB sources "*/*.cpp")

add_library(Olympus ${sources})