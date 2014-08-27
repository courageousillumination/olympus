#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/mesh.hpp"

#include "render_fixture.hpp"

using namespace olympus;

class MeshTest : public RenderTest {
protected:
    virtual void SetUp() {
        mesh = new Mesh(2, Mesh::TRIANGLES);
    }
    
    virtual void TearDown() {
        delete mesh;
    }
    
    Mesh *mesh;
};

TEST_F (MeshTest, PrimativeTypes) {
    Mesh mesh1(0, Mesh::TRIANGLE_FAN);
    Mesh mesh2(0, Mesh::TRIANGLE_STRIP);
}

TEST_F (MeshTest, IncorrectUpload) {
    const float data[] = { 1.0, 2.0 };
    mesh->set_vertex_attribute(0, 1, 1, data);
    mesh->set_vertex_attribute(1, 1, 2, data);
}