#include "render/world.hpp"

using namespace olympus;

World::World() {
    _root = this;
}
RenderEngine *World::get_render_engine() {
    return _render_engine;
}