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
    render_engine->set_world(this);
}

void World::add_renderable(Renderable *renderable) {
    _renderables.insert(renderable);
}
void World::remove_renderable(Renderable *renderable) {
    _renderables.erase(renderable);
}

void World::add_light(Light *light) {
    _lights.insert(light);
}
void World::remove_light(Light *light) {
    _lights.erase(light);
}

std::set<Renderable *> World::get_renderables() {
    return _renderables;
}

std::set<Light *> World::get_lights() {
    return _lights;
}