#include <gtest/gtest.h>

#include "olympus.hpp"

#include "common/olympus_environment.hpp"
#include "common/square.hpp"
#include "common/test_block.hpp"
#include "common/fixtures/world_fixture.hpp"

using namespace olympus;

/**
 * This tests creates a new square and then moves
 * the light around making sure that it properly affects
 * the square.
 */
class LightTest : public WorldedTest {
protected:
    virtual void SetUp() {
        WorldedTest::SetUp();
        Renderer *r = new Renderer(FLAT_LIGHT_VERTEX_SHADER,
                                   FLAT_LIGHT_FRAGMENT_SHADER);
        s = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 0.0, 1.0, 0.0, r);
        world->add_child(s);
    }
    
    virtual void TearDown() {
        world->remove_child(s);
        destroy_square(s);
        WorldedTest::TearDown();
    }
    
    Renderable *s;
};

TEST_F (LightTest, DirectionalLight) {
    glm::vec3 pre_light, light1, light2, light_behind;
    //Check the scene before any light has been added
    window->render();
    pre_light = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    //Now we add a light pointing directly at the square
    Light *light = new Light(Light::DIRECTIONAL);
    light->set_type(Light::DIRECTIONAL);
    EXPECT_EQ(Light::DIRECTIONAL, light->get_type());
    light->set_direction(0.0, 0.0, -1.0);
    //NOTE: This might be better suited for a unit test...
    float x, y, z;
    light->get_direction(x, y, z);
    EXPECT_EQ(0.0, x); EXPECT_EQ(0.0, y); EXPECT_EQ(-1.0, z);
    world->add_child(light);
    window->render();
    
    light1 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_GT(light1[1], pre_light[1]);
    EXPECT_EQ(glm::vec3(0.0, 1.0, 0.0), light1);
        
    //Change the direction, now the illumination should be less.
    light->set_direction(0.0, -1.0, -1.0);

    
    window->render();
    light2 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_LT(light2[1], light1[1]);
    EXPECT_GT(light2[1], pre_light[1]);
    
    //Now we put the light in the back
    light->set_direction(0.0, 0.0, 1.0);
    window->render();
    light_behind = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_EQ(pre_light[1], light_behind[1]);
    
    //Finally we clean up
    world->remove_child(light);
    delete light;
}

TEST_F (LightTest, DirectionalLightWithViewpoint) {
    Viewpoint *viewpoint= new Viewpoint;
    viewpoint->set_near(0.1);
    viewpoint->set_position(0.0f, 0.0f, -1.0f);
    viewpoint->set_orientation(0.0f, 3.14f, 0.0);
    screen->set_viewpoint(viewpoint);
    
    glm::vec3 pre_light, light1, light2, light_behind;
    //Check the scene before any light has been added
    window->render();
    pre_light = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    //Now we add a light pointing directly at the square
    Light *light = new Light(Light::DIRECTIONAL);
    light->set_direction(glm::vec3(0.0, 0.0, -1.0));
    world->add_child(light);
    window->render();
    
    light1 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_GT(light1[1], pre_light[1]);
    EXPECT_EQ(glm::vec3(0.0, 1.0, 0.0), light1);
    
    //Now we put the light in the back
    light->set_direction(0.0, 0.0, 1.0);
    window->render();
    light_behind = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_EQ(pre_light[1], light_behind[1]);
    
    //Finally we clean up
    world->remove_child(light);
    delete light;
    delete viewpoint;
}

TEST_F (LightTest, DirectionalLightWithShadows) {
     glm::vec3 pre_light, lit, shadow;
    //Check the scene before any light has been added (this should be the same
    //as the shadowed image);
    window->render();
    pre_light = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    //Now we add a light pointing directly at the square
    Light *light = new Light(Light::DIRECTIONAL);
    light->set_direction(0.0, 0.0, -1.0);
    world->add_child(light);
    window->render();
    
    lit = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    //Now we add a block between us and the light source
    Renderer *r = new Renderer(FLAT_LIGHT_VERTEX_SHADER,
                            FLAT_LIGHT_FRAGMENT_SHADER);
    Renderable *s1 = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 0.0, 1.0, 0.0, r);
    s1->set_position(0.0, 0.0, 1.0f);
    world->add_child(s1);
    
    window->render();
    shadow = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(pre_light, shadow);
    EXPECT_LT(shadow[1], lit[1]);
    
    //Clean up
    world->remove_child(s1);
    destroy_square(s1);
    
    world->remove_child(light);
    delete light;
}
