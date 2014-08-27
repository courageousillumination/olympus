#include <gtest/gtest.h>

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "olympus.hpp"
#include "render/viewpoint.hpp"

using namespace olympus;

class ViewpointTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        viewpoint = new Viewpoint;
    }
    
    virtual void TearDown() {
    }
    
    Viewpoint *viewpoint;
};

TEST_F (ViewpointTest, MatrixCalculations) {
    //All three should default to the same value
    EXPECT_EQ(glm::mat4(1.0f), viewpoint->get_view_matrix());
    
    viewpoint->set_position(1.0f, 0.0f, 0.0f);
    glm::mat4 expected_matrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 0.0f),
                                            glm::vec3(1.0f, 0.0f,-1.0f),
                                            glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(expected_matrix, viewpoint->get_view_matrix());
     
    //Test the projection_matrix
    viewpoint->set_perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f);
    glm::mat4 expected_perspective = glm::perspective(1.0f, 4.0f / 3.0f, 1.0f, 2.0f);
    expected_matrix = expected_perspective * expected_matrix;
    EXPECT_EQ(expected_perspective, viewpoint->get_projection_matrix());
    EXPECT_EQ(expected_matrix, viewpoint->get_view_projection_matrix());
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