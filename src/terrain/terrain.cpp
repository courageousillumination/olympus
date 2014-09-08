#include "terrain/terrain.hpp"

#include "debug/logger.hpp"

using namespace olympus;

Terrain::Terrain() {

}

Terrain::~Terrain() {
    
}

Mesh *Terrain::generate_mesh() {
    return generate_mesh(0);
}

/*static void calculate_normal(float *verts, float *normals, unsigned *indices) {
    
    
    glm::vec3 p1 = glm::vec3(verts[*indices * 3], verts[*indices * 3 + 1], verts[*indices * 3 + 2]);
    glm::vec3 p2 = glm::vec3(verts[*(indices + 1) * 3 + 4], verts[*indices * 3 + 4], verts[triangle_index + 5]);
    glm::vec3 p3 = glm::vec3(verts[triangle_index + 6], verts[triangle_index + 7], verts[triangle_index + 8]);
    
    glm::vec3 u = p2 - p1;
    glm::vec3 v = p3 - p1;
    
    glm::vec3 normal = glm::vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
    
    normals[triangle_index + 0] = normal[0];
    normals[triangle_index + 1] = normal[1];
    normals[triangle_index + 2] = normal[2];

    normals[triangle_index + 3] = normal[0];
    normals[triangle_index + 4] = normal[1];
    normals[triangle_index + 5] = normal[2];

    normals[triangle_index + 6] = normal[0];
    normals[triangle_index + 7] = normal[1];
    normals[triangle_index + 8] = normal[2];

}*/

static void create_height_map(unsigned width, unsigned  height, glm::vec3 *verts, unsigned seed) {
    for (unsigned i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            float x_dist = i - width / 2.0f;
            float y_dist = j - height / 2.0f;
            verts[i * width + j][1] = -0.5f * sqrt(x_dist * x_dist + y_dist * y_dist); 
        }   
    }
}

static void calculate_normals(unsigned width, unsigned height, glm::vec3 *verts, glm::vec3 *normals, unsigned *indices) {
    for (unsigned i = 0; i < (width - 1)* (height - 1) * 6 + 6; i+= 3) {
        glm::vec3 p1 = verts[indices[i]];
        glm::vec3 p2 = verts[indices[i + 1]];
        glm::vec3 p3 = verts[indices[i + 2]];
        
        glm::vec3 normal = glm::cross(p2 - p1, p3 - p1);
        normals[indices[i]] += normal;
        normals[indices[i + 1]] += normal;
        normals[indices[i + 2]] += normal;
    }
    //Now we go through and normalize
    for (unsigned i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            normals[i * width + j] = glm::normalize(normals[i * width + j]);
        }   
    }
}

Mesh *Terrain::generate_mesh(unsigned seed) {
    Mesh *mesh = new Mesh(3, Mesh::TRIANGLES);
    
    unsigned width = 10, height = 10;
    float cell_size = 1.0f;
    
    glm::vec3 *verts = new glm::vec3[width * height];
    glm::vec3 *normals = new glm::vec3[width * height];
    glm::vec3 *colors = new glm::vec3[width * height];

    unsigned *indices = new unsigned[(width - 1)* (height - 1) * 6 + 6];
    unsigned *ind = indices;
    
    // Init all verts to be a square grid
    for (unsigned i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            unsigned index = i * width + j;
            verts[index] = glm::vec3(i * cell_size, 0.0f, j * cell_size);
            normals[index] = glm::vec3(0.0f, 0.0f, 0.0f);
            colors[index] = glm::vec3(0.0f, 1.0f, 0.0f);
            
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
    
    create_height_map(width, height, verts, seed);
    calculate_normals(width, height, verts, normals, indices);

    mesh->set_vertex_attribute(0, 3, width * height, (float *)verts);
    mesh->set_vertex_attribute(1, 3, width * height, (float *)colors);
    mesh->set_vertex_attribute(2, 3, width * height, (float *)normals);
    mesh->set_indices((width - 1)* (height - 1)* 6 + 6, indices);
    
    delete []indices;
    delete []verts;
    delete []normals;
    delete []colors;
    
    return mesh;
}
