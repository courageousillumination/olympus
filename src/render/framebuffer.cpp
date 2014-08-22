#include <GL/glew.h>

#include "debug/logger.hpp"

#include "render/framebuffer.hpp"

using namespace olympus;

Framebuffer::Framebuffer() {
    glGenFramebuffers(1, &_frame_buffer_id);
    
    bind();
    
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
    
    //Add a depth buffer. Really this should probably not be in the constructor. TODO: Fix this
    GLuint depth_renderbuffer;
    glGenRenderbuffers(1, &depth_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 640, 480);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_renderbuffer);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG(Logger::ERROR, "Failed to create framebuffer");
    }
    
    unbind();
}

Framebuffer::~Framebuffer() {
    delete _color_0_texture;
    glDeleteFramebuffers(1, &_frame_buffer_id);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer_id);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Texture *Framebuffer::get_color_texture() {
    return _color_0_texture;
}