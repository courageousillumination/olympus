#include "render/world.hpp"

using namespace olympus;

World::World() {
    _root = this;
}

void World::add_renderable(Renderable *renderable) {
    _renderables.insert(renderable);
}
void World::remove_renderable(Renderable *renderable) {
    _renderables.erase(renderable);
}

void World::add_light(Light *light) {
    _lights.push_back(light);
}
void World::remove_light(Light *light) {
    for (std::vector<Light *>::iterator l = _lights.begin();
         l != _lights.end();
         ++l) {
        if (light == *l) {
            _lights.erase(l);
            return;
        }
    }
}

std::set<Renderable *> World::get_renderables() {
    return _renderables;
}

std::vector<Light *> World::get_lights() {
    return _lights;
}