#include <gtest/gtest.h>

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "olympus.hpp"
#include "world/viewpoint.hpp"

using namespace olympus;

class ViewpointTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        viewpoint = new Viewpoint;
    }
    
    virtual void TearDown() {
        delete viewpoint;
    }
    
    Viewpoint *viewpoint;
};

TEST_F (ViewpointTest, MatrixCalculations) {
    glm::mat4 expected_view_matrix, expected_matrix, expected_perspective_matrix;
    //All three should default to the same value
    EXPECT_EQ(glm::mat4(1.0f), viewpoint->get_view_matrix());
    
    viewpoint->set_position(1.0f, 0.0f, 0.0f);
    expected_view_matrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 0.0f),
                                            glm::vec3(1.0f, 0.0f,-1.0f),
                                            glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(expected_view_matrix, viewpoint->get_view_matrix());
     
    //Test the projection_matrix
    viewpoint->set_perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f);
    expected_perspective_matrix = glm::perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f);
    expected_matrix = expected_perspective_matrix * expected_view_matrix;
    EXPECT_EQ(expected_perspective_matrix, viewpoint->get_projection_matrix());
    EXPECT_EQ(expected_matrix, viewpoint->get_view_projection_matrix());
    
    //Test the projection matrix with individual getters and setters
    viewpoint->set_fov(1.2f);
    viewpoint->set_ratio(4.5f / 3.0f);
    viewpoint->set_near(0.5f);
    viewpoint->set_far(3.0f);
    
    expected_perspective_matrix = glm::perspective(1.2f, 4.5f / 3.0f, 0.5f, 3.0f);
    expected_matrix = expected_perspective_matrix * expected_view_matrix;
    EXPECT_EQ(expected_perspective_matrix, viewpoint->get_projection_matrix());
    EXPECT_EQ(expected_matrix, viewpoint->get_view_projection_matrix());
    EXPECT_EQ(1.2f, viewpoint->get_fov());
    EXPECT_EQ(4.5f /3.0f, viewpoint->get_ratio());
    EXPECT_EQ(0.5f, viewpoint->get_near());
    EXPECT_EQ(3.0f, viewpoint->get_far());
}

TEST_F(ViewpointTest, TestInheritance) {
    WorldObject *parent = new WorldObject;
    
    parent->add_child(viewpoint);
    parent->set_position(glm::vec3(1.0f, 0.0f, 0.0f));
    
    EXPECT_NE(glm::mat4(1.0f), viewpoint->get_view_matrix());
    
    viewpoint->set_position(1.0f, 0.0f, 0.0f);
    glm::mat4 expected_matrix = glm::lookAt(glm::vec3(2.0f, 0.0f, 0.0f),
                                            glm::vec3(2.0f, 0.0f,-1.0f),
                                            glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(expected_matrix, viewpoint->get_view_matrix());
     
    //Test the projection_matrix
    viewpoint->set_perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f);
    glm::mat4 expected_perspective = glm::perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f);
    expected_matrix = expected_perspective * expected_matrix;
    EXPECT_EQ(expected_perspective, viewpoint->get_projection_matrix());
    EXPECT_EQ(expected_matrix, viewpoint->get_view_projection_matrix());
    
    delete parent;
}