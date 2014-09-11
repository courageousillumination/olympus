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
class LightTest : public WorldedTest {
protected:
    virtual void SetUp() {
        WorldedTest::SetUp();
        Renderer *r = new Renderer(FLAT_LIGHT_VERTEX_SHADER,
                                   FLAT_LIGHT_FRAGMENT_SHADER);
        s = create_cube(0, 0, 0, 1, r);
        world->add_child(s);
        
        viewpoint = new Viewpoint;
        viewpoint->set_near(0.1);
        viewpoint->set_position(0.0f, 0.0f, 2.0f);
        screen->set_viewpoint(viewpoint);
        
        light = new Light(Light::DIRECTIONAL);
    }
    
    virtual void TearDown() {
        world->remove_child(s);
        delete viewpoint;
        delete light;
        destroy_cube(s);
        WorldedTest::TearDown();
        
    }
    
    Renderable *s;
    Viewpoint *viewpoint;
    Light *light;
};

TEST_F (LightTest, DirectionalLight) {
    glm::vec3 pre_light, light1, light2, light_behind;
    //Check the scene before any light has been added
    window->render();
    pre_light = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    //Now we add a light pointing directly at the square
    
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
    EXPECT_GT(light1[0], pre_light[0]);
    EXPECT_EQ(glm::vec3(1.0, 0.0, 0.0), light1);
        
    //Change the direction, now the illumination should be less.
    light->set_direction(0.0, -1.0, -1.0);
    window->render();
    light2 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_LT(light2[0], light1[0]);
    EXPECT_GT(light2[0], pre_light[0]);
    
    //Now we put the light in the back
    light->set_direction(0.0, 0.0, 1.0);
    window->render();
    light_behind = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_EQ(pre_light[0], light_behind[0]);
    
    //Finally we clean up

}

TEST_F (LightTest, DirectionalLightWithViewpoint) {
    viewpoint->set_position(0, 0, 0.5);
    viewpoint->set_orientation(glm::angleAxis(-3.14f, glm::vec3(1, 0, 0)));
        
    glm::vec3 pre_light, light1, light2, light_behind;
    //Check the scene before any light has been added
    window->render();
    pre_light = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    //Now we add a light pointing directly at the square
    light->set_direction(glm::vec3(0.0, 0.0, -1.0));
    world->add_child(light);
    window->render();
    
    light1 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_GT(light1[0], pre_light[0]);
    EXPECT_EQ(glm::vec3(1.0, 0.0, 0.0), light1);
    
    //Now we put the light in the back
    light->set_direction(0.0, 0.0, 1.0);
    window->render();
    light_behind = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    EXPECT_EQ(pre_light[0], light_behind[0]);
    
    //Finally we clean up
    world->remove_child(light);
}

TEST_F (LightTest, DirectionalLightWithShadows) {
    Renderer *old_renderer = s->asset->get_renderer();
    Renderer *new_renderer = new Renderer(SHADOW_VERTEX_SHADER,
                                          SHADOW_FRAGMENT_SHADER);
    
    Renderable *s1 = new Renderable;
    s->asset->set_renderer(new_renderer);
    s1->asset = s->asset;
    
    
    glm::vec3 pre_light, lit, shadow;
    //Check the scene before any light has been added (this should be the same
    //as the shadowed image)
    window->render();
    pre_light = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    //Now we add a light pointing directly at the square
    light->set_direction(0.0, 0.0, -1.0);
    world->add_child(light);
    render_engine->enable_shadows();
    window->render();
    
    lit = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    //Now we add a block between us and the light source
    s1->set_position(0.0, 0.0, 3.0f);
    world->add_child(s1);
    
    window->render();
    shadow = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(pre_light, shadow);
    EXPECT_LT(shadow[0], lit[0]);
    
    //Clean up
    world->remove_child(s1);
    world->remove_child(light);
    s->asset->set_renderer(old_renderer);
    delete s1;
    delete new_renderer;
}


TEST_F (LightTest, TwoDirectionalLights) {
    Light *light2 = new Light(Light::DIRECTIONAL);
    
    //Check both sides of the cube before anything has been added
    glm::vec3 pre_light1, pre_light2, one_light1, one_light2, two_lights1, two_lights2;
    
    window->render();
    pre_light1 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    viewpoint->set_position(0.0, 0.0, -2.0f);
    viewpoint->set_orientation(glm::angleAxis(-3.14f, glm::vec3(1, 0, 0)));
    
    window->render();
    pre_light2 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(pre_light1, pre_light2);
    
    //Now we add a light from one direction and check both
    viewpoint->set_position(0.0, 0.0, 2.0f);
    viewpoint->set_orientation(glm::angleAxis(0.0f, glm::vec3(1, 0, 0)));
    light->set_direction(0, 0, -1.0);
    world->add_child(light);
    
    window->render();
    one_light1 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    viewpoint->set_position(0.0, 0.0, -2.0f);
    viewpoint->set_orientation(glm::angleAxis(-3.14f, glm::vec3(1, 0, 0)));
    
    window->render();
    one_light2 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_GT(one_light1[0], one_light2[0]);
    EXPECT_EQ(pre_light1, one_light2);
    
    //Next we add our second light and we expect both sides to be equally illuminated
    viewpoint->set_position(0.0, 0.0, 2.0f);
    viewpoint->set_orientation(glm::angleAxis(0.0f, glm::vec3(1, 0, 0)));
    light2->set_direction(0, 0, 1.0);
    world->add_child(light2);
    
    window->render();
    two_lights1 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    viewpoint->set_position(0.0, 0.0, -2.0f);
    viewpoint->set_orientation(glm::angleAxis(-3.14f, glm::vec3(1, 0, 0)));
    
    window->render();
    two_lights2 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(two_lights1, two_lights2);
    
    //Clean up
    world->remove_child(light);
    world->remove_child(light2);
    delete light2;
}


TEST_F (LightTest, TwoDirectionalLightsWithShadows) {
    glm::vec3 pre_shadow1, pre_shadow2, post_shadow1, post_shadow2;
    
    Renderer *old_renderer = s->asset->get_renderer();
    Renderer *new_renderer = new Renderer(SHADOW_VERTEX_SHADER,
                                          SHADOW_FRAGMENT_SHADER);
    s->asset->set_renderer(new_renderer);
    
    Renderable *s1 = new Renderable;
    s1->asset = s->asset;
    s1->set_position(0, 0, -3.0f);
    Renderable *s2 = new Renderable;
    s2->asset = s->asset;
    s2->set_position(0, 0, 3.0f);
    
    Light *light2 = new Light(Light::DIRECTIONAL);
    light2->set_direction(0, 0, 1.0f);
    light->set_direction(0, 0, -1.0f);
    world->add_child(light);
    world->add_child(light2);
    world->add_child(s1);
    world->add_child(s2);
   
    window->render();
    pre_shadow1 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    viewpoint->set_position(0.0, 0.0, -2.0f);
    viewpoint->set_orientation(glm::angleAxis(-3.14f, glm::vec3(1, 0, 0)));
    window->render();
    pre_shadow2 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(pre_shadow1, pre_shadow2);
    EXPECT_EQ(glm::vec3(1, 0, 0), pre_shadow1);
    
    render_engine->enable_shadows();
    viewpoint->set_position(0.0, 0.0, 2.0f);
    viewpoint->set_orientation(glm::angleAxis(0.0f, glm::vec3(1, 0, 0)));
    window->render();
    
    post_shadow1 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    viewpoint->set_position(0.0, 0.0, -2.0f);
    viewpoint->set_orientation(glm::angleAxis(-3.14f, glm::vec3(1, 0, 0)));
    window->render();
    post_shadow2 = average_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    
    EXPECT_EQ(post_shadow1, post_shadow2);
    EXPECT_LT(post_shadow1[0], 1);
    EXPECT_LT(post_shadow2[0], 1);
    
    //Clean up
    world->remove_child(light);
    world->remove_child(light2);
    world->remove_child(s1);
    world->remove_child(s2);
    s->asset->set_renderer(old_renderer);
    delete light2;
    delete s1;
    delete s2;
    delete new_renderer;
}