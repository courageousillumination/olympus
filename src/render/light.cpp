#include "debug/logger.hpp"
#include "render/light.hpp"
#include "render/world.hpp"

using namespace olympus;

Light::Light(Light::LightType type) {
    _type = type;
    _viewpoint = new Viewpoint;
    if (type == DIRECTIONAL) {
        _viewpoint->set_ortho(glm::vec2(-10, 10),
                              glm::vec2(-10, 10),
                              glm::vec2(-10, 10));
    }
}

Light::~Light() {
    delete _viewpoint;
}

void Light::set_parent(WorldObject *parent) {
    if (_parent != nullptr) {
        //We need to deregister ourselvels
        _parent->get_root()->remove_light(this);
    }
    _parent = parent;
    if (parent != nullptr) {
        parent->get_root()->add_light(this);
    }
}

void Light::set_direction(float x, float y, float z) {
    _direction = glm::normalize(glm::vec3(x, y, z));
}

void Light::set_direction(glm::vec3 direction) {
    _direction = glm::normalize(direction);
}

void Light::get_direction(float &x, float &y, float &z) {
    x = _direction[0];
    y = _direction[1];
    z = _direction[2];
}

glm::vec3 Light::get_direction() {
    return _direction;
}

void Light::set_type(LightType type) {
    _type = type;
}

Light::LightType Light::get_type() {
    return _type;
}

Viewpoint *Light::get_viewpoint() {
    return _viewpoint;
}

void Light::_update_viewpoint() {
    if (_type == DIRECTIONAL) {
        //_viewpoint->set_orientation(_direction);
    }
}