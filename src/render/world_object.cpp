#include "render/world_object.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

using namespace olympus;

WorldObject::WorldObject() {
    _parent = nullptr;
    _root = nullptr;
    _scale = glm::vec3(1.0, 1.0, 1.0);
    _position = glm::vec3(0.0, 0.0, 0.0);
    _update_model_matrix();
}

void WorldObject::set_position(glm::vec3 position) {
    _position = position;
    _update_model_matrix();
}
void WorldObject::set_position(float x, float y, float z) {
    _position = glm::vec3(x, y, z);
    _update_model_matrix();
}
void WorldObject::set_scale(glm::vec3 scale) {
    _scale = scale;
    _update_model_matrix();
}
void WorldObject::set_scale(float x, float y, float z) {
    _scale = glm::vec3(x, y, z);
    _update_model_matrix();
}
void WorldObject::set_parent(WorldObject *parent) {
    _parent = parent;
    _update_model_matrix();
}
void WorldObject::add_child(WorldObject *child) {
    _children.insert(child);
    if (child->_parent != this) {
        child->set_parent(this);
    }
}

void WorldObject::remove_child(WorldObject *child) {
    //TODO
}

glm::vec3 WorldObject::get_position() {
    return _position;
}
void WorldObject::get_position(float &x, float &y, float &z) {
    x = _position[0];
    y = _position[1];
    z = _position[2];
}
glm::vec3 WorldObject::get_scale() {
    return _scale;
}
void WorldObject::get_scale(float &x, float &y, float &z) {
    x = _scale[0];
    y = _scale[1];
    z = _scale[2];
}

WorldObject *WorldObject::get_parent() {
    return _parent;
}
std::set<WorldObject *> WorldObject::get_children() {
    return _children;
}

glm::mat4 WorldObject::get_model_matrix() {
    return _model_matrix;
}
World *WorldObject::get_root() {
    return _root;
}

void WorldObject::_update_model_matrix() {
    if (_parent != nullptr) {
        _model_matrix = glm::translate(_position) * glm::scale(_scale) * _parent->get_model_matrix();
    } else {
         _model_matrix = glm::translate(_position) * glm::scale(_scale);
    }
    
    //Update children
    for(auto child : _children) {
        child->_update_model_matrix();
    }
}