#include "terrain/water.hpp"
#include "debug/logger.hpp"
#include "render/shaders.hpp"

#include <glm/gtc/noise.hpp>
#include <GL/glew.h>
using namespace olympus;

Water::Water() {
    asset = new Asset;

}

Water::~Water() { 
    delete asset;
}

Renderer *Water::_get_renderer() {
    return new Renderer(WATER_VERTEX_SHADER,
                        SHADOW_FRAGMENT_SHADER);
}

Mesh *Water::_generate_mesh() {
    Mesh *mesh = new Mesh(4, Mesh::TRIANGLES);
    
    unsigned width = 64, height = 64;
    float cell_size = 0.1f;
    
    glm::vec3 *verts = new glm::vec3[width * height];
    glm::vec3 *normals = new glm::vec3[width * height];
    glm::vec3 *colors = new glm::vec3[width * height];
    glm::vec2 *height_maps_locations = new glm::vec2[width * height];

    unsigned *indices = new unsigned[(width - 1) * (height - 1) * 6];
    unsigned *ind = indices;
    
    // Init all verts to be a square grid
    for (unsigned i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            unsigned index = i * width + j;
            verts[index] = glm::vec3(i * cell_size, 0.0f, j * cell_size);
            normals[index] = glm::vec3(0.0f, 1.0f, 0.0f);
            colors[index] = glm::vec3(0.0f, 0.0f, 1.0f);
            height_maps_locations[index] = glm::vec2((float) i / width, (float) j / height);
            
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
    
    mesh->set_vertex_attribute(0, 3, width * height, (float *)verts);
    mesh->set_vertex_attribute(1, 3, width * height, (float *)colors);
    mesh->set_vertex_attribute(2, 3, width * height, (float *)normals);
    mesh->set_vertex_attribute(3, 2, width * height, (float *)height_maps_locations);
    mesh->set_indices((width - 1) * (height - 1) * 6, indices);
    
    delete []indices;
    delete []verts;
    delete []normals;
    delete []colors;
    
    return mesh;
}

Texture *Water::_generate_heightmap(unsigned width, unsigned height) {
    Texture *texture = new Texture(Texture::TEXTURE_2D);
    
    float *data = new float[width * height];
    float *data_pointer = data;
    for (unsigned i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            *data_pointer++ = glm::perlin(glm::vec2((float) i / 5, (float) j / 5));//sin((float) i / 10);
        }
    }
    
    texture->load_data(1, width, height, data);
    //TODO: This is a hack. This does not belong here.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    return texture;
}

void Water::generate() {
    //Here we generate a mesh, renderer and textures for our water
    asset->set_mesh(_generate_mesh());
    asset->set_renderer(_get_renderer());
    
    //Generate a height map texture
    asset->add_texture(_generate_heightmap(64, 64), 0);
    asset->add_texture(_generate_heightmap(64, 64), 1);
}

void Water::destroy() {
    delete asset->get_mesh();
    delete asset->get_renderer();
}

float x_position = 0.0f;
float x_position2 = 0.0f;
void Water::pre_render() {
    x_position += 0.001f;
    x_position2 += 0.003f;
    asset->get_renderer()->set_uniform(std::string("height_map1"), 0);
    asset->get_renderer()->set_uniform(std::string("height_map2"), 1);
    
    asset->get_renderer()->set_uniform(std::string("height_map_offset1"), glm::vec2(x_position, 0));
    asset->get_renderer()->set_uniform(std::string("height_map_offset2"), glm::vec2(x_position2, 0));
}