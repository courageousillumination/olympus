#include <gtest/gtest.h>

#include "olympus.hpp"

#include "common/olympus_environment.hpp"
#include "common/cube.hpp"
#include "common/test_block.hpp"
#include "common/fixtures/world_fixture.hpp"

using namespace olympus;

/**
 * This tests creates a new square and then moves
 * the light around making sure that it properly affects
 * the square.
 */
class SkyboxTest : public WorldedTest {
protected:
    virtual void SetUp() {
        WorldedTest::SetUp();
        // Create the red sky
        skybox = new Skybox(OLYMPUS_ROOT_DIR "/test/assets/red-texture.png",
                            OLYMPUS_ROOT_DIR "/test/assets/blue-texture.png",
                            OLYMPUS_ROOT_DIR "/test/assets/red-texture.png",
                            OLYMPUS_ROOT_DIR "/test/assets/red-texture.png",
                            OLYMPUS_ROOT_DIR "/test/assets/red-texture.png",
                            OLYMPUS_ROOT_DIR "/test/assets/green-texture.png");
        world->set_skybox(skybox);

        viewpoint = new Viewpoint;
        screen->set_viewpoint(viewpoint);
    }
    
    virtual void TearDown() {
        delete viewpoint;
        delete skybox;
        WorldedTest::TearDown();
        
    }
    Skybox *skybox;
    Viewpoint *viewpoint;
};

TEST_F (SkyboxTest, RendersInAllDirections) {
    window->render();
    
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1.0, 0.0, 0.0));
    
    viewpoint->set_orientation(glm::angleAxis(-3.14f, glm::vec3(1, 0, 0)));
    window->render();
    
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 0.0, 1.0));
    
    
    viewpoint->set_orientation(glm::angleAxis(3.14f / 2.0f, glm::vec3(1, 0, 0)));
    window->render();
    
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
}