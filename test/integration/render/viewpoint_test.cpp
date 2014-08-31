#include <gtest/gtest.h>

#include "olympus.hpp"

#include "common/square.hpp"
#include "common/test_block.hpp"
#include "common/olympus_environment.hpp"
#include "common/fixtures/world_fixture.hpp"

using namespace olympus;

class ViewpointTestIntegration : public WorldedTest {
protected:
    virtual void SetUp() {
        WorldedTest::SetUp();
        viewpoint = new Viewpoint;
    }
    
    virtual void TearDown() {
        delete viewpoint;
        WorldedTest::TearDown();
    }
    Viewpoint *viewpoint;
};

TEST_F (ViewpointTestIntegration, AffectsImageOnScreen) {
    Renderable *g = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 0.0, 1.0, 0.0);
    world->add_child(g);
    window->render();
    
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    
    screen->set_viewpoint(viewpoint);
    viewpoint->set_position(0, 0, 2.0f);
    window->render();
    EXPECT_FALSE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    EXPECT_TRUE(expect_color_block(DEFAULT_WIDTH / 4, DEFAULT_HEIGHT / 4, 
                                   DEFAULT_WIDTH / 2, DEFAULT_HEIGHT / 2, 0.0, 1.0, 0.0));
    
    destroy_square(g);
}

TEST_F (ViewpointTestIntegration, WorksFromBehind) {
    Renderable *g = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 0.0, 1.0, 0.0);
    world->add_child(g);
    window->render();
    
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    
    screen->set_viewpoint(viewpoint);
    viewpoint->set_position(0, 0, -2.0f);
    viewpoint->set_orientation(0.0, 3.14, 0.0);
    window->render();
    EXPECT_FALSE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    EXPECT_TRUE(expect_color_block(DEFAULT_WIDTH / 4, DEFAULT_HEIGHT / 4, 
                                   DEFAULT_WIDTH / 2, DEFAULT_HEIGHT / 2, 0.0, 1.0, 0.0));
    
    destroy_square(g);
}