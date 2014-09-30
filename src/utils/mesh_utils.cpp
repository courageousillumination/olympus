#include "utils/mesh_utils.hpp"

unsigned *olympus::generate_plane_indices(unsigned width, unsigned height) {
    unsigned *indices = new unsigned[(width - 1) * (height - 1) * 6];
    unsigned *ind = indices;
    
    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            //No need to make indices for the last row/column
            if (i == width - 1 or j == height - 1) {
                continue;
            }
            
            *ind++ = i * width + j;
            *ind++ = (i + 1) * width + j;
            *ind++ = (i + 1) * width + j + 1;
            
            *ind++ = i * width + j;
            *ind++ = (i + 1) * width + j + 1;
            *ind++ = i * width + j + 1;
            
        }
    }
    
    return indices;
}

glm::vec3 *olympus::generate_normals(glm::vec3 *verts, unsigned *indices,
                                     unsigned num_indices, unsigned num_verts) {
    glm::vec3 *normals = new glm::vec3[num_verts]; 
    for (unsigned i = 0; i < num_verts; i++) {
        normals[i] = glm::vec3(0, 0, 0);
    }
    
    for (unsigned i = 0; i < num_indices; i+= 3) {
        glm::vec3 p1 = verts[indices[i]];
        glm::vec3 p2 = verts[indices[i + 1]];
        glm::vec3 p3 = verts[indices[i + 2]];
        
        glm::vec3 normal = glm::cross(p2 - p1, p3 - p1);
        normals[indices[i]] += normal;
        normals[indices[i + 1]] += normal;
        normals[indices[i + 2]] += normal;
    }
    
    for (unsigned i = 0; i < num_verts; i++) {
        normals[i] = glm::normalize(normals[i]);
    }
    
    return normals;
}

glm::vec3 olympus::position_helper(unsigned width, unsigned height, unsigned x, unsigned y, void *scale) {
    float cell_size = *(float *)scale;
    return glm::vec3(cell_size * x, 0, cell_size * y);
}

glm::vec2 olympus::position_helper_2D(unsigned width, unsigned height, unsigned x, unsigned y, void *scale) {
    float cell_size = *(float *)scale;
    return glm::vec2(cell_size * x, cell_size * y);
}

/**
 * Simple function to make a square out of a height map.
 */
glm::vec3 olympus::heightmap_sub(unsigned width, unsigned height, unsigned x, unsigned y, void *height_map) {
    return glm::vec3((float) x / width, ((float *) height_map)[y * width + x], (float) y / width);
}