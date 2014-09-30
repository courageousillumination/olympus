#include <random>

#include "terrain/terrain.hpp"

#include "utils/mesh_utils.hpp"

#include "debug/logger.hpp"

using namespace olympus;

void Terrain::_generate_height_map_helper(float *values, unsigned x1, unsigned y1, 
                                          unsigned x2, unsigned y2, unsigned level, float max_displacement) {
    if (level == 0) {
        return;
    }
    
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-max_displacement, max_displacement);
    
    // Diamond step
    for (unsigned i = x1 + level; i < x2; i+=level) {
        for(unsigned j = y1 + level; j < y2; j+= level) {
            float a = values[(i - level) * _size + j - level];
            float b = values[i * _size +j-level];
            float c = values[(i - level) * _size +j];
            float d = values[i * _size +j];
            values[(i - level / 2)*_size + j - level / 2] = (a + b + c + d) / 4.0f + distribution(generator);
        }
    }
    
    // Square step
    for (unsigned i = x1 + 2 * level; i < x2; i += level) {
        for (unsigned j = y1 + 2 * level; j < y2; j+= level) {
            float a = values[(i - level) * _size + j - level];
            float b = values[i * _size +j-level];
            float c = values[(i - level) * _size +j];
            float e = values[(i - level/2) * _size +j - level/2];
            
            values[(i - level) * _size +j - level / 2] = (a + c + e + values[(i - 3 * level / 2) * _size +j - level / 2])  / 4.0f + distribution(generator);
            values[(i - level / 2) * _size +j - level] = (a + b + e + values[(i - level / 2) * _size +j - 3 * level / 2])  / 4.0f + distribution(generator);
        }
    }
    
    // Recurse
    _generate_height_map_helper(values, x1, y1, x2, y2, 
                                level / 2, max_displacement * _falloff);

}

float *Terrain::_generate_height_map() {
    float *values = new float[_size * _size];
    // Initalize
    for (unsigned i = 0; i < _size * _size; i++) {
        values[i] = 0.0f;
    }
    _generate_height_map_helper(values, 0, 0, _size, _size, _size, _max_displacement);
    return values;
}

Mesh *Terrain::_generate_mesh() {
    Mesh *mesh = new Mesh(3, Mesh::TRIANGLES);
    
    float *height_map = get_height_map();
    
    glm::vec3 *verts = create_plane(_size, _size, heightmap_sub, height_map);
    glm::vec3 *colors = create_plane(_size, _size, glm::vec3(0.0f, 1.0f, 0.0f));
    unsigned *indices = generate_plane_indices(_size, _size);
    glm::vec3 *normals = generate_normals(verts, indices, (_size - 1) * (_size - 1) * 6, _size * _size);
    
    mesh->set_vertex_attribute(0, 3, _size * _size, (float *)verts);
    mesh->set_vertex_attribute(1, 3, _size * _size, (float *)colors);
    mesh->set_vertex_attribute(2, 3, _size * _size, (float *)normals);
    mesh->set_indices((_size - 1) * (_size - 1) * 6, indices);
    
    // Clean up
    delete []verts;
    delete []colors;
    delete []indices;
    delete []normals;
    
    return mesh;
}

Terrain::Terrain(Renderer *renderer) {
    _height_map = nullptr;
    _seed = 0;
    _size = 1 << 6; // Default to 64 x 64
    
    // These have been determined by experimentation to find something that looks good.
    _max_displacement = 2.0f;
    _falloff = 0.4f;
    
    asset = new Asset;
    asset->set_mesh(_generate_mesh());
    asset->set_renderer(renderer);
    
}

Terrain::Terrain(Renderer *renderer,
                 unsigned seed, unsigned detail, float max_displacement, float falloff) {
    _height_map = nullptr;
    _seed = seed;
    _size = 1 << detail;
    _max_displacement = max_displacement;
    _falloff = falloff;
    
    asset = new Asset;
    asset->set_mesh(_generate_mesh());
    asset->set_renderer(renderer);
}

Terrain::~Terrain() {
    // Clean up by destroying my asset and the mesh it contains
    delete asset->get_mesh(); 
    delete asset;
    delete []_height_map;
}

float *Terrain::get_height_map() {
    if (_height_map == nullptr) {
        _height_map = _generate_height_map();
    }
    return _height_map;
}