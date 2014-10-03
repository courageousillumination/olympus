#include <GL/glew.h>

#include "debug/logger.hpp"

#include "render/resource_manager.hpp"
#include "render/framebuffer.hpp"

using namespace olympus;

Framebuffer::Framebuffer(unsigned width, unsigned height) {
    _width = width;
    _height = height;
    _frame_buffer_id = ResourceManager::get_instance().get_resource(ResourceManager::FRAMEBUFFER); 
    
    _depth_texture = nullptr;
    
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &_max_color_attachments);
    _color_textures = new Texture*[_max_color_attachments];
    for (int i = 0; i < _max_color_attachments; i++) {
        _color_textures[i] = nullptr;
    }
}

Framebuffer::~Framebuffer() {
    delete []_color_textures;
    ResourceManager::get_instance().release_resource(ResourceManager::FRAMEBUFFER, _frame_buffer_id);
}

void Framebuffer::attach_color_texture(Texture *texture, unsigned slot) {
    _color_textures[slot] = texture;
    
    //Clear out the texture
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_id);
    texture->bind();
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, texture->_texture_id, slot);
    
    //Finally we need to set up the draw buffers
    unsigned num_buffers = 0;
    GLenum draw_buffers[_max_color_attachments];
    for (int i = 0; i < _max_color_attachments; i++) {
        if (_color_textures[i] != nullptr) {
            draw_buffers[num_buffers++] = GL_COLOR_ATTACHMENT0 + i;
        }
    }
    glDrawBuffers(num_buffers, draw_buffers);
}

void Framebuffer::attach_depth_texture(Texture *texture) {
    _depth_texture = texture;
    
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_id);
    texture->bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->_texture_id, 0);   
}

Texture *Framebuffer::get_color_texture(unsigned slot) {
    return _color_textures[slot];
}

Texture *Framebuffer::get_depth_texture() {
    return _depth_texture;
}

unsigned Framebuffer::get_internal_id() {
    return _frame_buffer_id;
}