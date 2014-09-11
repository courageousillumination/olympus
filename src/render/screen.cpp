#include <GL/glew.h>
#include <GL/gl.h>

#include "debug/logger.hpp"

#include "render/screen.hpp"
#include "render/renderer.hpp"
#include "render/shaders.hpp"
#include "render/mesh.hpp"

using namespace olympus;

Screen::Screen() {
    _framebuffer = new Framebuffer;
    _graphics_state = new GraphicsState;
    _viewpoint = nullptr;
    _world = nullptr;
    _render_engine = nullptr;
}

Screen::~Screen() {
    delete _graphics_state;
    delete _framebuffer;
}

void Screen::render() {
    _framebuffer->bind();
    
    GraphicsStateManager::get_instance().push(_graphics_state);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (_world != nullptr) {
        _render_engine->render(_viewpoint, _world);
    }
    
    GraphicsStateManager::get_instance().pop();
    
    _framebuffer->unbind();
};

Framebuffer *Screen::get_framebuffer() {
    return _framebuffer;
}

void Screen::set_world(World *world) {
    _world = world;
}

void Screen::set_viewpoint(Viewpoint *viewpoint) {
    _viewpoint = viewpoint;
}

void Screen::set_render_engine(RenderEngine *render_engine) {
    _render_engine = render_engine;
}

Viewpoint *Screen::get_viewpoint() {
    return _viewpoint;
}

World *Screen::get_world() {
    return _world;
}

RenderEngine *Screen::get_render_engine() {
    return _render_engine;
}

GraphicsState *Screen::get_graphics_state() {
    return _graphics_state;
}
