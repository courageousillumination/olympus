#include "fx/skybox.hpp"
#include "render/shaders.hpp"

using namespace olympus;

// Simple 1x1x1 cube, centered at 0.
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

Skybox::Skybox(const char *front, const char *back,
               const char *left, const char *right,
               const char *top, const char *bottom) {
    Texture *texture = new Texture(Texture::CUBE_MAP);
    texture->load_images(front, back, left, right, top, bottom);
    Mesh *mesh = new Mesh(1, Mesh::TRIANGLES);
    mesh->set_vertex_attribute(0, 3, 36, (float *)cube_vertex_data);
    
    asset = new Asset;
    asset->add_texture(texture);
    asset->set_mesh(mesh);
    asset->set_renderer(new Renderer(SKYBOX_VERTEX_SHADER,
                                     SKYBOX_FRAGMENT_SHADER));
}

Skybox::~Skybox() {
    delete asset->get_texture(0);
    delete asset->get_mesh();
    delete asset->get_renderer();
    delete asset;
}

void Skybox::render() {

}