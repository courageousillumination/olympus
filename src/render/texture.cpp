#include <exception>
#include <stdexcept>

#include <SOIL/SOIL.h>
#include <GL/glew.h>

#include "debug/logger.hpp"

#include "render/resource_manager.hpp"
#include "render/texture.hpp"

using namespace olympus;

static unsigned enum_convertor(Texture::Target target) {
    switch (target) {
        case Texture::TEXTURE_2D:
            return GL_TEXTURE_2D;
        case Texture::TEXTURE_3D:
            return GL_TEXTURE_3D;
        default:
            return GL_NONE;
    }
}

static unsigned parameter_value_convertor(Texture::ParameterValue value) {
    switch (value) {
        case Texture::Repeat:
            return GL_REPEAT;
        case Texture::Clamp:
            return GL_CLAMP;
        default:
            return GL_NONE;
    }
}

Texture::Texture() {
    _target = Texture::NONE;
    _texture_id = 0;
}

Texture::Texture(Texture::Target target) {
    _target = target;
    _texture_id = ResourceManager::get_instance().get_resource(ResourceManager::TEXTURE);

    bind();
    glTexParameteri(enum_convertor(_target), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(enum_convertor(_target), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Texture::~Texture() {
    // If for some reason we have the target none, we probably shouldn't release it.-
    // Generally, this will only be used in testing.
    if (_target != Texture::NONE) {
        ResourceManager::get_instance().release_resource(ResourceManager::TEXTURE, _texture_id);
    }
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

void Texture::load_data(unsigned num_channels, unsigned width, unsigned height, float *data) {
    bind();
    switch(num_channels) {
        case 1:
            glTexImage2D(enum_convertor(_target), 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, data);
            break;
        case 3:
            glTexImage2D(enum_convertor(_target), 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, data); 
            break;
        default:
            LOG(Logger::WARN, "Tried to load data into a texture with an unspported number of channels %d", num_channels);
    }
}

void Texture::bind() {
    glBindTexture(enum_convertor(_target), _texture_id);
}

void Texture::set_parameter(Texture::Parameter parameter, Texture::ParameterValue value) {
    bind();
    switch (parameter) {
        case Texture::Wrap:
            _wrapT = value;
            _wrapS = value;
            glTexParameteri(_target, GL_TEXTURE_WRAP_S, parameter_value_convertor(value));
            glTexParameteri(_target, GL_TEXTURE_WRAP_T, parameter_value_convertor(value));
            break;
        case Texture::WrapS:
            _wrapS = value;
            glTexParameteri(_target, GL_TEXTURE_WRAP_S, parameter_value_convertor(value));
            break;
        case Texture::WrapT:
            _wrapT = value;
            glTexParameteri(_target, GL_TEXTURE_WRAP_T, parameter_value_convertor(value));
            break;
    }
}

Texture::ParameterValue Texture::get_parameter(Texture::Parameter parameter) {
    switch (parameter) {
        case Texture::Wrap:
            if (_wrapT == _wrapS) {
                return _wrapS;
            }
            return Invalid;
        case Texture::WrapT:
            return _wrapT;
        case Texture::WrapS:
            return _wrapS;
        default:
            LOG(Logger::WARN, "Attempted to get an invalid parameter from a texture (%d)", parameter);
            return Invalid;
    }
}