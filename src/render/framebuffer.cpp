#include <GL/glew.h>

#include "debug/logger.hpp"

#include "render/resource_manager.hpp"
#include "render/framebuffer.hpp"

using namespace olympus;

Framebuffer::Framebuffer() {
    _frame_buffer_id = ResourceManager::get_instance().get_resource(ResourceManager::FRAMEBUFFER); 
    
    //Get the current framebuffer id
    //unsigned previous_id = GraphicsStateManager::get_instance().get_head()->framebuffer->_frame_buffer_id;
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
}

Framebuffer::~Framebuffer() {
    delete _color_0_texture;
    delete _depth_texture;
    ResourceManager::get_instance().release_resource(ResourceManager::FRAMEBUFFER, _frame_buffer_id);
}

Texture *Framebuffer::get_color_texture() {
    return _color_0_texture;
}

Texture *Framebuffer::get_depth_texture() {
    return _depth_texture;
}

unsigned Framebuffer::get_internal_id() {
    return _frame_buffer_id;
}