find_package(GTest)

include_directories(${OLYMPUS_SOURCE_DIR}/inc ${OLYMPUS_SOURCE_DIR}/test)

link_directories (${OLYMPUS_BINARY_DIR}/src)

FILE(GLOB common "common/*.cpp")

FILE(GLOB unittests "unit/*/*_test.cpp")

FILE(GLOB integrationtests "integration/*/*_test.cpp")

add_executable(Tests olympus_test.cpp ${common} ${unittests} ${integrationtests})

target_link_libraries(Tests Olympus ${GLFW_LIBRARIES} ${GL_LIBRARY} gtest)
