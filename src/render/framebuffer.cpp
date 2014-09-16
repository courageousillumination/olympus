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
    
    //Get the current framebuffer id
    //unsigned previous_id = GraphicsStateManager::get_instance().get_head()->framebuffer->_frame_buffer_id;
    
    /*
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_id);
    //glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_id);
    
    //Create a texture to attach to color 0
    _color_0_texture = new Texture(Texture::TEXTURE_2D);
    
    //Directly set the image to be empty (NOTE: This assumes the constructor
    //binds the texture).
    //TODO: Parameterize the width/height
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480,
                 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    //Attach to the framebuffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         _color_0_texture->_texture_id, 0);
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
    
    _depth_texture = new Texture(Texture::TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT32, 640, 480, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _depth_texture->_texture_id, 0);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG(Logger::ERROR, "Failed to create framebuffer");
    }
    
    //unbind();
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    */
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
    
    glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT32, _width, _height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
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