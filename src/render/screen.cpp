#include <GL/glew.h>
#include <GL/gl.h>

#include "render/screen.hpp"
#include "render/renderer.hpp"
#include "render/shaders.hpp"
#include "render/mesh.hpp"

using namespace olympus;

Screen::Screen() {
    /** As soon as we're done debugging this entire thing should be dropped **/
    /*if (mesh == nullptr) {
        glActiveTexture(GL_TEXTURE0);
        texture = new Texture(Texture::TEXTURE_2D);
        texture->load_image("/home/tristan/Development/olympus/texture.jpg");
        texture->bind();
        renderer = new Renderer(TEXTURE_VERTEX_SHADER,
                                          TEXTURE_FRAGMENT_SHADER);
        renderer->bind();
        
        mesh = new Mesh(2, Mesh::TRIANGLES);
        mesh->set_vertex_attribute(0, 3, 3, g_vertex_buffer_data);
        mesh->set_vertex_attribute(1, 2, 3, cube_texcoords);
    }*/
    
    _framebuffer = new Framebuffer;
}

void Screen::render() {
    _framebuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    
    /** All the things following this should be done in the world 
    renderer->bind();
    texture->bind();
    mesh->bind();
    mesh->draw();
     Finish world draw **/
    
    _world->render();
    
    _framebuffer->unbind();
};

Framebuffer *Screen::get_framebuffer() {
    return _framebuffer;
}

void Screen::set_world(World *world) {
    _world = world;
}