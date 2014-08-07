#include "render/standard_render_engine.hpp"

using namespace olympus;

void StandardRenderEngine::render() {
    Renderable *current = nullptr;
    for (std::set<Renderable *>::iterator it = _renderables.begin();
         it != _renderables.end(); it++) {
        current = *it;
        if (current->asset->get_textures()[0] != nullptr) {
            current->asset->get_textures()[0]->bind();
        }
        current->asset->get_renderer()->bind();
        current->asset->get_mesh()->bind();
        current->asset->get_mesh()->draw();
    }
}