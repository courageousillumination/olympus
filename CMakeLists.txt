cmake_minimum_required(VERSION 2.6)

project(OLYMPUS)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -Werror -Wall -g") # Make sure everything is safe
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(src)
add_subdirectory(samples)
