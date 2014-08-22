#include <gtest/gtest.h>

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "olympus.hpp"
#include "render/viewpoint.hpp"

#include "render_fixture.hpp"
#include "utils.hpp"

using namespace olympus;

class ViewpointTest : public RenderTest {
protected:
    virtual void SetUp() {
        //Create a new renderable that will cover the entire screen (without a viewpoint)
        r = create_square(-1.0f, -1.0f, 2.0f, 2.0f, 1.0, 0.0, 0.0);
        //Create a new viewpoint
        viewpoint = new Viewpoint;
        
        _window->world->add_child(r);
        _window->screen->set_viewpoint(viewpoint);
    }
    
    virtual void TearDown() {
        _window->world->remove_child(r);
        delete viewpoint;
        destroy_square(r);
    }
    
    Viewpoint *viewpoint;
    Renderable *r;
};

TEST_F (ViewpointTest, MatrixCalculations) {
    //All three should default to the same value
    EXPECT_EQ(viewpoint->get_view_matrix(), glm::mat4(1.0f));
    
    viewpoint->set_position(1.0f, 0.0f, 0.0f);
    glm::mat4 expected_matrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 0.0f),
                                            glm::vec3(1.0f, 0.0f,-1.0f),
                                            glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(viewpoint->get_view_matrix(), expected_matrix);
     
    //Test the projection_matrix
    viewpoint->set_perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f);
    expected_matrix = glm::perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f) * expected_matrix;
    EXPECT_EQ(viewpoint->get_projection_matrix(), glm::perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f));
    EXPECT_EQ(viewpoint->get_view_projection_matrix(), expected_matrix);
}

TEST_F (ViewpointTest, AffectsImage) {
    //_window->window->render();
    
    //EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1.0, 0.0, 0.0));
}
