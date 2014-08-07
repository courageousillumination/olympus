#include "render/world_object.hpp"

using namespace olympus;

void WorldObject::set_position(glm::vec3 position) {
    _position = position;
}
void WorldObject::set_position(float x, float y, float z) {
    _position = glm::vec3(x, y, z);
}
void WorldObject::set_scale(glm::vec3 scale) {
    _scale = scale;
}
void WorldObject::set_scale(float x, float y, float z) {
    _scale = glm::vec3(x, y, z);
}
void WorldObject::set_parent(WorldObject *parent) {
    _parent = parent;
}
void WorldObject::add_child(WorldObject *child) {
    _children.insert(child);
    if (child->_parent != this) {
        child->set_parent(this);
    }
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