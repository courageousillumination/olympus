#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/renderer.hpp"

#include "common/olympus_environment.hpp"
#include "common/fixtures/window_fixture.hpp"

using namespace olympus;

TEST_F (WindowedTest, TestConstruction) {
    Renderer renderer(OLYMPUS_ROOT_DIR "/test/shaders/good_v.glsl", OLYMPUS_ROOT_DIR "/test/shaders/good_f.glsl");
    EXPECT_NE(renderer.get_internal_id(), 0);
}

TEST_F (WindowedTest, TestFailures) {
    get_test_appender()->set_expect_error(true);
    
    Renderer renderer1("bad file name", "bad file name");
    EXPECT_EQ(renderer1.get_internal_id(), 0);
    EXPECT_TRUE(get_test_appender()->contains_string("Failed to open shader bad file name"));
    Renderer renderer2(OLYMPUS_ROOT_DIR "/test/shaders/bad_v.glsl", OLYMPUS_ROOT_DIR "/test/shaders/bad_f.glsl");
    EXPECT_EQ(renderer2.get_internal_id(), 0);
    Renderer renderer3(OLYMPUS_ROOT_DIR "/test/shaders/bad_link_v.glsl", OLYMPUS_ROOT_DIR "/test/shaders/bad_link_f.glsl");
    EXPECT_EQ(renderer3.get_internal_id(), 0);
    
    get_test_appender()->set_expect_error(false);
    
}
