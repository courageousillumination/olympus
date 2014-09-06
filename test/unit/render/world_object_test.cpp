#include <gtest/gtest.h>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "olympus.hpp"
#include "render/world_object.hpp"

using namespace olympus;

class WorldObjectTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        object = new WorldObject;
    }
    
    virtual void TearDown() {
        delete object;
    }
    
    WorldObject *object;
};

/**
 * When I set the position, orientation, and scale the world object
 * should move accordingly
 */
TEST_F (WorldObjectTest, PositionOrientationAndScale) {
    float x, y, z;
    
    //Test scale/position setters using glm vecs3
    object->set_position(glm::vec3(1, 0, 0));
    object->set_scale(glm::vec3(1, 1.5, 1));
    
    EXPECT_EQ(glm::vec3(1, 0, 0), object->get_position());
    EXPECT_EQ(glm::vec3(1, 1.5, 1), object->get_scale());
    object->get_position(x, y, z);
    EXPECT_EQ(x, 1); EXPECT_EQ(y, 0); EXPECT_EQ(z, 0);
    object->get_scale(x, y, z);
    EXPECT_EQ(x, 1); EXPECT_EQ(y, 1.5); EXPECT_EQ(z, 1);
    
    //Test scale/position setters using floats
    object->set_position(2, 3, 4);
    object->set_scale(5, 6, 7);
    
    EXPECT_EQ(glm::vec3(2, 3, 4), object->get_position());
    EXPECT_EQ(glm::vec3(5, 6, 7), object->get_scale());
    object->get_position(x, y, z);
    EXPECT_EQ(x, 2); EXPECT_EQ(y, 3); EXPECT_EQ(z, 4);
    object->get_scale(x, y, z);
    EXPECT_EQ(x, 5); EXPECT_EQ(y, 6); EXPECT_EQ(z, 7);
    
    //Test orientation getters and setters using quats
    object->set_orientation(glm::quat(1.0f, 0.0f, 0.0f, -1.0f));
    EXPECT_EQ(glm::quat(1.0f, 0.0f, 0.0f, -1.0f), object->get_orientation());
}

/**
 * When I set the position, orientation and scale the model matrix should return
 * a modified value
 */
TEST_F (WorldObjectTest, ModelMatrix) {
    object->set_position(1, 2, 3);
    object->set_scale(0.5, 0.5, 0.5);
    
    EXPECT_EQ(glm::translate(glm::vec3(1.0, 2.0, 3.0)) * glm::scale(glm::vec3(0.5, 0.5, 0.5)), object->get_model_matrix());
}

/**
 * When I move the parent, the child should move as well.
 */
TEST_F (WorldObjectTest, InheritsPositionOneLevel) {
    WorldObject *parent = new WorldObject;
    
    parent->set_position(1, 0, 0);
    parent->add_child(object);
    
    EXPECT_EQ(glm::translate(glm::vec3(1, 0, 0)), parent->get_model_matrix());
    EXPECT_EQ(glm::translate(glm::vec3(1, 0, 0)), object->get_model_matrix());
    
    object->set_position(2, 0, 0);
    EXPECT_EQ(glm::translate(glm::vec3(1, 0, 0)), parent->get_model_matrix());
    EXPECT_EQ(glm::translate(glm::vec3(3, 0, 0)), object->get_model_matrix());
    
    parent->set_position(-1, 0, 0);
    EXPECT_EQ(glm::translate(glm::vec3(-1, 0, 0)), parent->get_model_matrix());
    EXPECT_EQ(glm::translate(glm::vec3(1, 0, 0)), object->get_model_matrix());
    
    delete parent;
}

TEST_F(WorldObjectTest, InheritsPositionTwoLevels) {
    WorldObject *parent = new WorldObject;
    WorldObject *grand_parent = new WorldObject;
    
    grand_parent->add_child(parent);
    parent->add_child(object);
    
    grand_parent->set_position(glm::vec3(1, 0, 0));
    
    EXPECT_EQ(glm::translate(glm::vec3(1, 0, 0)), parent->get_model_matrix());
    EXPECT_EQ(glm::translate(glm::vec3(1, 0, 0)), object->get_model_matrix());
    
    object->set_position(2, 0, 0);
    EXPECT_EQ(glm::translate(glm::vec3(1, 0, 0)), parent->get_model_matrix());
    EXPECT_EQ(glm::translate(glm::vec3(3, 0, 0)), object->get_model_matrix());
    
    //When I remove the parent from the grand parent the child should update
    grand_parent->remove_child(parent);
    EXPECT_EQ(glm::translate(glm::vec3(0, 0, 0)), parent->get_model_matrix());
    EXPECT_EQ(glm::translate(glm::vec3(2, 0, 0)), object->get_model_matrix());
    
    delete parent;
    delete grand_parent;
}