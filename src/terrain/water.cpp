#include "terrain/water.hpp"
#include "debug/logger.hpp"
#include "render/shaders.hpp"

#include "utils/mesh_utils.hpp"

#include <glm/gtc/noise.hpp>
#include <GL/glew.h>
using namespace olympus;

Water::Water(unsigned detail, float wave_height,  float wave_width) {
    _size = 1 << detail;
    _wave_height = wave_height;
    _wave_width = wave_width;
    _time = 0.0f;
    asset = new Asset;
    
    //Here we generate a mesh, renderer and textures for our water
    asset->set_mesh(_generate_mesh());
    asset->set_renderer(_get_renderer());
    
    //Generate a height map texture
    asset->add_texture(_generate_heightmap(), 0);
    asset->add_texture(_generate_heightmap(), 1);
}

Water::~Water() {
    delete asset->get_texture(0);
    delete asset->get_texture(1);
    delete asset->get_mesh();
    delete asset->get_renderer();
    delete asset;
}

Renderer *Water::_get_renderer() {
    return new Renderer(WATER_VERTEX_SHADER,
                        FLAT_LIGHT_FRAGMENT_SHADER);
}

Mesh *Water::_generate_mesh() {
    Mesh *mesh = new Mesh(3, Mesh::TRIANGLES);
    
    float scale = 1.0f / _size;
    glm::vec3 *verts = create_plane(_size, _size, position_helper, &scale);
    glm::vec3 *colors = create_plane(_size, _size, glm::vec3(0.0f, 1.0f, 1.0f));
    glm::vec2 *height_maps_locations = create_plane(_size, _size, position_helper_2D, &scale);
    unsigned *indices = generate_plane_indices(_size, _size);
    
    mesh->set_vertex_attribute(0, 3, _size * _size, (float *)verts);
    mesh->set_vertex_attribute(1, 3, _size * _size, (float *)colors);
    mesh->set_vertex_attribute(3, 2, _size * _size, (float *)height_maps_locations);
    mesh->set_indices((_size - 1) * (_size - 1) * 6, indices);
    
    delete []indices;
    delete []verts;
    delete []colors;
    
    return mesh;
}

Texture *Water::_generate_heightmap() {
    Texture *texture = new Texture(Texture::TEXTURE_2D);
    
    float *data = new float[_size * _size];
    
    for (unsigned i = 0; i < _size; i++) {
        for (unsigned j = 0; j < _size; j++) {
            data[i * _size + j] = glm::perlin(glm::vec2((float) i / _wave_width,
                                                        (float) j / _wave_width)) * _wave_height;
        }
    }
    
    texture->load_data(1, _size, _size, data);
    
    //TODO: This is a hack. This does not belong here.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    return texture;
}

void Water::simulate() {
    _time += 0.005f;
}

void Water::pre_render() {
    asset->get_renderer()->set_uniform(std::string("height_map1"), 0);
    asset->get_renderer()->set_uniform(std::string("height_map2"), 1);
    
    asset->get_renderer()->set_uniform(std::string("height_map_offset1"), glm::vec2(_time, 0));
    asset->get_renderer()->set_uniform(std::string("height_map_offset2"), glm::vec2(0, _time));
}