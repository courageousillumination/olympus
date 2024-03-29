#include <GL/glew.h>
#include <GL/gl.h>

#include "debug/logger.hpp"

#include "render/renderer.hpp"
#include "render/shaders.hpp"
#include "render/mesh.hpp"

#include "window/screen.hpp"

using namespace olympus;

Screen::Screen(unsigned width, unsigned height) {
    _framebuffer = new Framebuffer(width, height);
    _graphics_state = new GraphicsState;
    _viewpoint = nullptr;
    _world = nullptr;
    _render_engine = nullptr;
    
    _color_texture = new Texture(Texture::TEXTURE_2D);
    _depth_texture = new Texture(Texture::TEXTURE_2D);
    
    _framebuffer->attach_color_texture(_color_texture, 0);
    _framebuffer->attach_depth_texture(_depth_texture);
    
    _graphics_state->framebuffer = _framebuffer;
}

Screen::~Screen() {
    delete _color_texture;
    delete _depth_texture;
    delete _graphics_state;
    delete _framebuffer;
}

void Screen::render() {
    //_framebuffer->bind();
    
    GraphicsStateManager::get_instance().push(_graphics_state);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (_world != nullptr) {
        _render_engine->render(_viewpoint, _world);
    }
    
    GraphicsStateManager::get_instance().pop();
    
    //_framebuffer->unbind();
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

Framebuffer *Screen::get_framebuffer() {
    return _framebuffer;
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
