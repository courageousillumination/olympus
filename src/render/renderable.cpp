#include "render/renderable.hpp"
#include "render/world.hpp"

using namespace olympus;

void Renderable::set_parent(WorldObject *parent) {
    _parent = parent;
    parent->get_root()->get_render_engine()->add_renderable(this);
}