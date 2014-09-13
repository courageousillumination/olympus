#include "world/renderable.hpp"
#include "world/world.hpp"

using namespace olympus;

void Renderable::set_parent(WorldObject *parent) {
    if (_parent != nullptr) {
        //We need to deregister ourselvels
        _parent->get_root()->remove_renderable(this);
    }
    _parent = parent;
    if (parent != nullptr) {
        parent->get_root()->add_renderable(this);
    }
}