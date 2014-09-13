#include <gtest/gtest.h>

#include "olympus.hpp"

#include "common/olympus_environment.hpp"
#include "common/square.hpp"
#include "common/test_block.hpp"
#include "common/fixtures/screen_fixture.hpp"

using namespace olympus;

class WorldTest : public ScreenedTest {
protected:
    virtual void SetUp() {
        ScreenedTest::SetUp();
        world = new World;
        render_engine = new StandardRenderEngine;
        
        screen->set_world(world);
        screen->set_render_engine(render_engine);
    }
    
    virtual void TearDown() {
        delete world;
        delete render_engine;
        ScreenedTest::TearDown();
    }
    
    RenderEngine *render_engine;
    World *world;
};

TEST_F (WorldTest, AddAndRemoveObjects) {
    EXPECT_EQ(world, screen->get_world());
    
    Renderable *g = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 0.0, 1.0, 0.0);
    world->add_child(g);
    window->render();
    
    std::set<WorldObject *> objects = world->get_children();
    EXPECT_EQ(1, objects.size());
    EXPECT_EQ(g, *(objects.cbegin()));
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 1.0, 0.0));
    
    world->remove_child(g);
    window->render();
    
    objects = world->get_children();
    EXPECT_EQ(0, objects.size());
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0, 0.0, 0.0));

    destroy_square(g);
}