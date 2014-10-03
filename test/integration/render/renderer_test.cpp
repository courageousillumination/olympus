#include <exception>
#include <stdexcept>

#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/renderer.hpp"

#include "common/olympus_environment.hpp"
#include "common/fixtures/window_fixture.hpp"

using namespace olympus;

TEST_F (WindowedTest, RendererTestConstruction) {
    Renderer renderer(OLYMPUS_ROOT_DIR "/test/shaders/good_v.glsl", OLYMPUS_ROOT_DIR "/test/shaders/good_f.glsl");
    EXPECT_NE(renderer.get_internal_id(), 0);
}

TEST_F (WindowedTest, RendererTestFailures) {
    get_test_appender()->set_expect_error(true);
    
    EXPECT_ANY_THROW(Renderer renderer1("bad file name", "bad file name"));
    EXPECT_TRUE(get_test_appender()->contains_string("Failed to open shader bad file name"));
    EXPECT_ANY_THROW(Renderer renderer2(OLYMPUS_ROOT_DIR "/test/shaders/bad_v.glsl", OLYMPUS_ROOT_DIR "/test/shaders/bad_f.glsl"));
    EXPECT_ANY_THROW(Renderer renderer3(OLYMPUS_ROOT_DIR "/test/shaders/bad_link_v.glsl", OLYMPUS_ROOT_DIR "/test/shaders/bad_link_f.glsl"));
    get_test_appender()->set_expect_error(false);
    
}

TEST_F (WindowedTest, RendererTestUniforms) {
    Renderer renderer(OLYMPUS_ROOT_DIR "/test/shaders/good_v.glsl", OLYMPUS_ROOT_DIR "/test/shaders/good_f.glsl");
    
    // Attempt to set all the uniforms. 
    renderer.set_uniform("vec3_uniform", glm::vec3(0, 0, 0));
    renderer.set_uniform("vec2_uniform", glm::vec2(0, 0));
    renderer.set_uniform("float_uniform", 1.0f);
    renderer.set_uniform("int_uniform", 1);
    renderer.set_uniform("mat4_uniform", glm::mat4(1.0f));
    
    glm::vec3 vec3_array[] = {glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)};
    glm::vec2 vec2_array[] = {glm::vec2(0, 0), glm::vec2(1, 1)};
    float float_array[] = {1.0f, 1.0f};
    int int_array[] = {1, 0};
    glm::mat4 mat4_array[] = {glm::mat4(1.0f), glm::mat4(1.0f)};
    renderer.set_uniform("vec3_uniforms", vec3_array, 2);
    renderer.set_uniform("vec2_uniforms", vec2_array, 2);
    renderer.set_uniform("float_uniforms", float_array, 2);
    renderer.set_uniform("int_uniforms", int_array, 2);
    renderer.set_uniform("mat4_uniforms", mat4_array, 2);
    
    get_test_appender()->set_expect_warning(true);
    
    renderer.set_uniform("not_there", 1.0f);
    EXPECT_TRUE(get_test_appender()->contains_string("Tried to fetch location of a non-existent uniform not_there from a shader"));
    
    
    get_test_appender()->set_expect_warning(false);
}