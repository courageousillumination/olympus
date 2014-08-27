find_package(GTest)

include_directories(${OLYMPUS_SOURCE_DIR}/inc ${OLYMPUS_SOURCE_DIR}/test)

link_directories (${OLYMPUS_BINARY_DIR}/src) 

#FILE(GLOB tests "*/*_test.cpp")

#add_executable(Tests olympus_test.cpp ${tests} render/utils.cpp render/render_fixture.cpp test_appender.cpp)

FILE(GLOB common "common/*.cpp")

FILE(GLOB unittests "unit/*/*_test.cpp")

FILE(GLOB integrationtests "integration/*/*_test.cpp")

add_executable(Tests olympus_test.cpp ${common} ${unittests} ${integrationtests})

target_link_libraries(Tests gtest Olympus ${GLFW_LIBRARIES} ${GL_LIBRARY})
