cmake_minimum_required(VERSION 2.6)

project(OLYMPUS)

set (OLYMPUS_VERSION_MAJOR 0)
set (OLYMPUS_VERSION_MINOR 1)

SET (CMAKE_CXX_FLAGS                "-Wall -Werror -fprofile-arcs -ftest-coverage -std=c++11 -g")

#set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Work-around http://www.cmake.org/Bug/bug_view_page.php?bug_id=6976 [^]
IF(NOT "${X11_Xxf86vm_LIB}")
    SET(X11_Xxf86vm_LIB "Xxf86vm")
ENDIF()

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU GLEW X11 ${X11_Xxf86vm_LIB} pthread Xrandr Xi Xcursor Xinerama SOIL)  

add_subdirectory(inc)
add_subdirectory(src)
add_subdirectory(samples)
add_subdirectory(test)
