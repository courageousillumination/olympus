#include <exception>
#include <stdexcept>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "debug/logger.hpp"

#include "render/texture.hpp"

using namespace olympus;

Texture::Texture(Texture::Target target) {
    _target = target;
    glGenTextures(1, &_texture_id);
    glBindTexture(GL_TEXTURE_2D, _texture_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Texture::~Texture() {
    glDeleteTextures(1, &_texture_id);
}

void Texture::load_image(const char *path) {
    if (_target != TEXTURE_2D) { 
        LOG(Logger::WARN, "Attempted to load an 2D image into a texture that is not 2D");
        return;
    }
    
    //Here we pass on to SOIL
    unsigned char *img = SOIL_load_image(path, &_width, &_height, NULL, 0);
    if (img == nullptr) {
        LOG(Logger::ERROR, "Failed to load image for texture %s", path);
        throw std::runtime_error("Failed to load image for texture");
    }
    LOG(Logger::DEBUG, "Loaded texture image %s (%dx%d)", path, _width, _height);
    
    //Upload the texture
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

    SOIL_free_image_data(img);
}

void Texture::bind() {
    switch (_target) {
        case TEXTURE_2D:
            glBindTexture(GL_TEXTURE_2D, _texture_id);
            break;
    }
}