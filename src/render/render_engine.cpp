#include "render/render_engine.hpp"

using namespace olympus;

void RenderEngine::add_renderable(Renderable *renderable) {
    _renderables.insert(renderable);
}
void RenderEngine::remove_renderable(Renderable *renderable) {
    _renderables.erase(renderable);
}