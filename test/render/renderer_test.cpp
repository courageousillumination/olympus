#include <gtest/gtest.h>

#include "olympus.hpp"
#include "../olympus_test.hpp"
#include "render/renderer.hpp"

#include "render_fixture.hpp"

using namespace olympus;

class RendererTest : public RenderTest {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {

    }    
};

TEST_F (RendererTest, TestConstruction) {
    Renderer renderer(OLYMPUS_ROOT_DIR "/test/render/shaders/good_v.glsl", OLYMPUS_ROOT_DIR "/test/render/shaders/good_f.glsl");
    EXPECT_NE(renderer.get_internal_id(), 0);
}

TEST_F (RendererTest, TestFailures) {
    logger_expect_error(true);
    
    Renderer renderer1("bad file name", "bad file name");
    EXPECT_EQ(renderer1.get_internal_id(), 0);
    Renderer renderer2(OLYMPUS_ROOT_DIR "/test/render/shaders/bad_v.glsl", OLYMPUS_ROOT_DIR "/test/render/shaders/bad_f.glsl");
    EXPECT_EQ(renderer2.get_internal_id(), 0);
    Renderer renderer3(OLYMPUS_ROOT_DIR "/test/render/shaders/bad_link_v.glsl", OLYMPUS_ROOT_DIR "/test/render/shaders/bad_link_f.glsl");
    EXPECT_EQ(renderer3.get_internal_id(), 0);
    
    logger_expect_error(false);
    
}
