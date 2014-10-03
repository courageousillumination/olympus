#include <gtest/gtest.h>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "olympus.hpp"
#include "utils/mesh_utils.hpp"

#define WIDTH 2
#define HEIGHT 2

using namespace olympus;

TEST (MeshUtilsTest, GenerateConstantPlane) {
    glm::vec3 *result = create_plane(WIDTH, HEIGHT, glm::vec3(1, 0, 0));
    for (unsigned i = 0; i < HEIGHT; i++) {
        for (unsigned j = 0; j < WIDTH; j++) {
            EXPECT_EQ(glm::vec3(1, 0, 0), result[i * WIDTH + j]);
        }
    }
    //Clean up
    delete []result;
}

static glm::vec3 generate_value(unsigned max_width, unsigned max_height, unsigned x, unsigned y, void *UNUSED) {
    return glm::vec3(x, y, 0);
}

TEST (MeshUtilsTest, GenerateFunctionalPlane) {
    glm::vec3 *result = create_plane(WIDTH, HEIGHT, generate_value, nullptr);
    for (unsigned i = 0; i < HEIGHT; i++) {
        for (unsigned j = 0; j < WIDTH; j++) {
            EXPECT_EQ(generate_value(WIDTH, HEIGHT, j, i, nullptr), result[i * WIDTH + j]);
        }
    }
    //Clean up
    delete []result;
}

TEST (MeshUtilsTest, PlaneIndices) {
    unsigned *indices = generate_plane_indices(2, 2);
    
    // Generate explicit indices
    unsigned expected[] = {
        0, 2, 3,
        0, 3, 1
    };
    
    for (unsigned i = 0; i < 6; i++) {
        EXPECT_EQ(expected[i], indices[i]);
    }
    
    //Clean up
    delete []indices;
}

TEST (MeshUtilsTest, GenerateNormals) {
    
    glm::vec3 verts[] = {
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(0, 0, 1)
    };
    
    unsigned indices[] = {
        0, 1, 2
    };
    
    glm::vec3 *normals = generate_normals(verts, indices, 3, 3);
    
    for (unsigned i = 0; i < 3; i++) {
        EXPECT_EQ(glm::vec3(0, -1, 0), normals[i]);
    }
    
    //Clean up
    delete []normals;
}

TEST (MeshUtilsTest, HelperFunctions) {
    float scale = 2.0f;
    EXPECT_EQ(glm::vec3(10, 0, 10), position_helper(10, 10, 5, 5, &scale));
    EXPECT_EQ(glm::vec2(10, 10), position_helper_2D(10, 10, 5, 5, &scale));
    
    float height_map[] = {1.0f};
    EXPECT_EQ(glm::vec3(0.0, 1.0, 0.0), heightmap_sub(10, 10, 0, 0, height_map));
}