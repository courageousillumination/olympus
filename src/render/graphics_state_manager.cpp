#include <GL/glew.h>

#include "debug/logger.hpp"
#include "render/graphics_state_manager.hpp"

using namespace olympus;

GraphicsState::GraphicsState() {
    wireframe = false;
    use_depth_test = true;
    depth_function = GL_LEQUAL;
    cull = false;
    cull_face = GL_BACK;
    blend = false;
    
    framebuffer = nullptr;
    
    next = nullptr;
}

//Individual setters, not part of the class, all of these are static methods.
static void enable_disable_general(GLenum target, bool flag) {
    if (flag) { 
        glEnable(target); 
    }
    else { 
        glDisable(target);
    }
}
static void set_wireframe(bool flag) {
    if (flag) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

static void set_framebuffer(Framebuffer *framebuffer) {
    if (framebuffer == nullptr) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->get_internal_id());
    }
}
    
void GraphicsStateManager::_apply_graphics_state(GraphicsState *state) {
    if (_head == nullptr or state->wireframe != _head->wireframe) {
        set_wireframe(state->wireframe);
    }
    if (_head == nullptr or state->use_depth_test != _head->use_depth_test) {
        enable_disable_general(GL_DEPTH_TEST, state->use_depth_test);
    }
    if (_head == nullptr or state->depth_function != _head->depth_function) {
        glDepthFunc(state->depth_function);
    }
    if (_head == nullptr or state->cull != _head->cull) {
        enable_disable_general(GL_CULL_FACE, state->cull);
    }
    if (_head == nullptr or state->cull_face != _head->cull_face) {
        glCullFace(state->cull_face);
    }
    if (_head == nullptr or state->framebuffer != _head->framebuffer) {
        set_framebuffer(state->framebuffer);
    }
    if (_head == nullptr or state->blend != _head->blend) {
        enable_disable_general(GL_BLEND, state->blend);
    }
}

GraphicsStateManager::GraphicsStateManager() {
    _head = nullptr;
}

GraphicsStateManager::~GraphicsStateManager() {
    while (_head != nullptr) {
        GraphicsState *next = _head->next;
        delete _head;
        _head = next;
    }
}

GraphicsStateManager& GraphicsStateManager::get_instance() {
    static GraphicsStateManager _manager;
    return _manager;
}

GraphicsState *GraphicsStateManager::get_head() {
    return _head;
}

void GraphicsStateManager::push(GraphicsState *state) {
    if (state == nullptr) { 
        LOG(Logger::WARN, "Tried to push a null graphics state onto the stack");
        return;
    }
    _apply_graphics_state(state);
    state->next = _head;
    _head = state;
}

void GraphicsStateManager::pop() {
    if (_head == nullptr) { 
        LOG(Logger::ERROR, "Tried to pop off of an empty graphics state stack.");
        return;
    }
    
    GraphicsState *next = _head->next;
    if (next != nullptr) {
        _apply_graphics_state(next);
    }
    _head = next;
}