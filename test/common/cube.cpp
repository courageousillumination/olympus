#include "cube.hpp"

using namespace olympus;


static const glm::vec3 cube_vertex_data[] = {
    //Front
    glm::vec3(-1.0, -1.0,  1.0),
    glm::vec3(1.0, -1.0,  1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    glm::vec3(-1.0, -1.0,  1.0),
    glm::vec3(-1.0,  1.0,  1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    //Left
    glm::vec3(-1.0, -1.0,  -1.0),
    glm::vec3(-1.0, -1.0,  1.0),
    glm::vec3(-1.0,  1.0,  1.0),
    
    glm::vec3(-1.0, -1.0,  -1.0),
    glm::vec3(-1.0,  1.0,  -1.0),
    glm::vec3(-1.0,  1.0,  1.0),
    
    //Right
    glm::vec3(1.0, -1.0,  -1.0),
    glm::vec3(1.0, -1.0,  1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    glm::vec3(1.0, -1.0,  -1.0),
    glm::vec3(1.0,  1.0,  -1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    //Back
    glm::vec3(-1.0, -1.0,  -1.0),
    glm::vec3(1.0, -1.0,  -1.0),
    glm::vec3(1.0,  1.0,  -1.0),
    
    glm::vec3(-1.0, -1.0,  -1.0),
    glm::vec3(-1.0,  1.0,  -1.0),
    glm::vec3(1.0,  1.0,  -1.0),
    
    //Top
    glm::vec3(-1.0, 1.0,  -1.0),
    glm::vec3(1.0, 1.0,  -1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    glm::vec3(-1.0, 1.0,  -1.0),
    glm::vec3(-1.0,  1.0,  1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    //Bottom
    glm::vec3(-1.0, -1.0, -1.0),
    glm::vec3(1.0, -1.0, -1.0),
    glm::vec3(1.0,  -1.0, 1.0),
    
    glm::vec3(-1.0, -1.0, -1.0),
    glm::vec3(-1.0,  -1.0, 1.0),
    glm::vec3(1.0,  -1.0, 1.0),
};


static glm::vec3 cube_color_data[] = {
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),

    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),

    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),


    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),

    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),

    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
};

static glm::vec3 cube_normals[] = {
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
};

Renderable *create_cube(float x, float y, float z, float size) {
    Renderer *renderer = new Renderer(FLAT_VERTEX_SHADER,
                                      FLAT_FRAGMENT_SHADER);
    return create_cube(x, y, z, size, renderer);
}

olympus::Renderable *create_cube(float x, float y, float z, float size, Renderer *renderer) {
    Mesh *mesh = new Mesh(3, Mesh::TRIANGLES);
    mesh->set_vertex_attribute(0, 3, 36, (float *)cube_vertex_data);
    mesh->set_vertex_attribute(1, 3, 36, (float *)cube_color_data);
    mesh->set_vertex_attribute(2, 3, 36, (float *)cube_normals);

    //Create an asset to wrap all of the above
    Asset *asset = new Asset;
    asset->set_mesh(mesh);
    asset->set_renderer(renderer);
    
    Renderable *renderable = new Renderable;
    renderable->asset = asset;
    renderable->set_scale(glm::vec3(size, size, size));
    renderable->set_position(x, y, z);
    
    return renderable;
}

void destroy_cube(Renderable *renderable) {
    delete renderable->asset->get_mesh();
    delete renderable->asset->get_renderer();
    delete renderable->asset;
    delete renderable;
}