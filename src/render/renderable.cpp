#include "render/renderable.hpp"
#include "render/world.hpp"

using namespace olympus;

void Renderable::set_parent(WorldObject *parent) {
    if (_parent != nullptr) {
        //We need to deregister ourselvels
        _parent->get_root()->get_render_engine()->remove_renderable(this);
    }
    _parent = parent;
    if (parent != nullptr) {
        parent->get_root()->get_render_engine()->add_renderable(this);
    }
}