include_directories(${GLFW_INCLUDE_DIRS})

include_directories(${OLYMPUS_SOURCE_DIR}/inc)

link_directories (${OLYMPUS_BINARY_DIR}/src) 

add_executable(BasicWindow main.cpp)

target_link_libraries(BasicWindow Olympus ${GLFW_LIBRARIES} ${GL_LIBRARY})
