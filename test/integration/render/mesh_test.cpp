#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/mesh.hpp"

#include "common/olympus_environment.hpp"
#include "common/fixtures/window_fixture.hpp"

using namespace olympus;

class MeshTest : public WindowedTest {
protected:
    virtual void SetUp() {
        WindowedTest::SetUp();
        mesh = new Mesh(2, Mesh::TRIANGLES);
    }
    
    virtual void TearDown() {
        delete mesh;
        WindowedTest::TearDown();
    }
    
    Mesh *mesh;
};

TEST_F (MeshTest, PrimativeTypes) {
    Mesh mesh1(1, Mesh::TRIANGLE_FAN);
    Mesh mesh2(1, Mesh::TRIANGLE_STRIP);
}

TEST_F (MeshTest, IncorrectUpload) {
    const float data[] = { 1.0, 2.0 };
    mesh->set_vertex_attribute(0, 1, 1, data);
    mesh->set_vertex_attribute(1, 1, 2, data);
    EXPECT_TRUE(get_test_appender()->contains_string("Mesh got unexpected number of vertices: expected 1, got 2"));
}