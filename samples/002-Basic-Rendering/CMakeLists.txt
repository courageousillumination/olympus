include_directories(${GLFW_INCLUDE_DIRS})

include_directories(${OLYMPUS_SOURCE_DIR}/inc)

link_directories (${OLYMPUS_BINARY_DIR}/src) 

add_executable(BasicRendering main.cpp)

target_link_libraries(BasicRendering Olympus ${GLFW_LIBRARIES} ${GL_LIBRARY})
