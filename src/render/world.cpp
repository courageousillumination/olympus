#include "render/world.hpp"

using namespace olympus;

World::World() {
    _root = this;
}
RenderEngine *World::get_render_engine() {
    return _render_engine;
}

void World::set_render_engine(RenderEngine *render_engine) {
    _render_engine = render_engine;
}