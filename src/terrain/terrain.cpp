#include <random>

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

void diamond_square(glm::vec3 *vertices, int row_size,
                    int x1, int y1, int x2, int y2,
                    int level, float max_displacement, float falloff) {
   
    if (level < 1) return;
    
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-max_displacement, max_displacement);
    
    //Diamond Step
    for (int i = x1 + level; i < x2; i+=level) {
        for(int j = y1 + level; j < y2; j+= level) {
            float a = vertices[(i - level) * row_size + j - level][1];
            float b = vertices[i * row_size +j-level][1];
            float c = vertices[(i - level) * row_size +j][1];
            float d = vertices[i * row_size +j][1];
            vertices[(i - level / 2)*row_size + j - level / 2][1] = (a + b + c + d) / 4.0f + distribution(generator);
        }
    }
    
    for (int i = x1 + 2 * level; i < x2; i += level) {
        for (int j = y1 + 2 * level; j < y2; j+= level) {
            float a = vertices[(i - level) * row_size + j - level][1];
            float b = vertices[i * row_size +j-level][1];
            float c = vertices[(i - level) * row_size +j][1];
            //float d = vertices[i][j][1];
            float e = vertices[(i - level/2) * row_size +j - level/2][1];
            
            vertices[(i - level) * row_size +j - level / 2][1] = (a + c + e + vertices[(i - 3 * level / 2) * row_size +j - level / 2][1])  / 4.0f + distribution(generator);
            vertices[(i - level / 2) * row_size +j - level][1] = (a + b + e + vertices[(i - level / 2) * row_size +j - 3 * level / 2][1])  / 4.0f + distribution(generator);
        }
    }
    diamond_square(vertices, row_size, x1, y1, x2, y2, level / 2, max_displacement * falloff, falloff);
}

static void create_height_map(unsigned width, unsigned  height, glm::vec3 *verts, unsigned seed) {
    diamond_square(verts, width, 0, 0, width, height, 64, 10.0f, 0.4f);
}

static void calculate_normals(unsigned width, unsigned height, glm::vec3 *verts, glm::vec3 *normals, unsigned *indices) {
    for (unsigned i = 0; i < (width - 1)* (height - 1) * 6; i+= 3) {
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
    
    unsigned width = 64, height = 64;
    float cell_size = 0.1f;
    
    glm::vec3 *verts = new glm::vec3[width * height];
    glm::vec3 *normals = new glm::vec3[width * height];
    glm::vec3 *colors = new glm::vec3[width * height];

    unsigned *indices = new unsigned[(width - 1) * (height - 1) * 6];
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
            
            
            *ind++ = (i + 1) * width + j + 1;
            *ind++ = (i + 1) * width + j;
            *ind++ = i * width + j;
            
            *ind++ = i * width + j + 1;
            *ind++ = (i + 1) * width + j + 1;
            *ind++ = i * width + j;
            
        }
    }
    
    create_height_map(width, height, verts, seed);
    calculate_normals(width, height, verts, normals, indices);

    mesh->set_vertex_attribute(0, 3, width * height, (float *)verts);
    mesh->set_vertex_attribute(1, 3, width * height, (float *)colors);
    mesh->set_vertex_attribute(2, 3, width * height, (float *)normals);
    mesh->set_indices((width - 1) * (height - 1) * 6, indices);
    
    delete []indices;
    delete []verts;
    delete []normals;
    delete []colors;
    
    return mesh;
}
