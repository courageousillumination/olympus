#include "render/render_engine.hpp"

using namespace olympus;

void RenderEngine::set_world(World *world) {
    _world = world;
}

World *RenderEngine::get_world() {
    return _world;
}