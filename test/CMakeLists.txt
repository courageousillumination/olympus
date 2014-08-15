find_package(GTest)

include_directories(${OLYMPUS_SOURCE_DIR}/inc)

link_directories (${OLYMPUS_BINARY_DIR}/src) 

FILE(GLOB tests "*/*_test.cpp")

add_executable(Tests olympus_test.cpp ${tests} render/utils.cpp render/render_fixture.cpp)

target_link_libraries(Tests gtest Olympus ${GLFW_LIBRARIES} ${GL_LIBRARY})
