cmake_minimum_required(VERSION 2.6)

project(OLYMPUS)

set (OLYMPUS_VERSION_MAJOR 0)
set (OLYMPUS_VERSION_MINOR 1)

SET (CMAKE_CXX_FLAGS                "-Wall -Werror -fprofile-arcs -ftest-coverage")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(inc)
add_subdirectory(src)
add_subdirectory(samples)
add_subdirectory(test)
