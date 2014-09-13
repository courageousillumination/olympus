#include "debug/logger.hpp"

#include "world/world.hpp"
#include "world/renderable.hpp"
#include "world/light.hpp"

#include "window/screen.hpp"

#include "render/standard_render_engine.hpp"
#include "render/shaders.hpp"

#include <GL/glew.h>

using namespace olympus;

static glm::mat4 bias_matrix = glm::mat4(0.5, 0.0, 0.0, 0.0,
                                         0.0, 0.5, 0.0, 0.0,
                                         0.0, 0.0, 0.5, 0.0,
                                         0.5, 0.5, 0.5, 1.0);

void StandardRenderEngine::pre_render_viewpoint(Viewpoint *viewpoint) {
    if (viewpoint == nullptr) {
        _view_matrix = glm::mat4(1.0f);
        _projection_matrix = glm::mat4(1.0f); 
    } else {
        _view_matrix = viewpoint->get_view_matrix();
        _projection_matrix = viewpoint->get_projection_matrix();
    }
}

void StandardRenderEngine::configure_renderer_viewpoint(Renderer *renderer) {
    renderer->set_uniform(std::string("projection_matrix"), _projection_matrix);    
}

void StandardRenderEngine::configure_object_viewpoint(Renderer *renderer, Renderable *renderable) {
    renderer->set_uniform(std::string("model_view_matrix"), _view_matrix * renderable->get_model_matrix());
}

void StandardRenderEngine::pre_render_lights(std::vector<Light *> &lights) {
    unsigned i;
    for (i = 0; i < lights.size() && i < MAX_LIGHT_SOURCES; i++) {
        glm::vec4 t = _view_matrix * glm::vec4(lights[i]->get_direction(), 0.0);
        _light_directions[i] = glm::vec3(t[0], t[1], t[2]);
        _use_lights[i] = 1;
    }
    while (i < MAX_LIGHT_SOURCES) {
        _use_lights[i++] = 0;
    }
}

void StandardRenderEngine::configure_renderer_lights(Renderer *renderer) {
    if (renderer->has_uniform(std::string("light_direction"))) {
        renderer->set_uniform(std::string("light_direction"), _light_directions, MAX_LIGHT_SOURCES);
    }
    renderer->set_uniform(std::string("use_lights"), _use_lights, MAX_LIGHT_SOURCES);
}

void StandardRenderEngine::enable_shadows() {
    _use_shadows = true;
    setup_shadows();
}

void StandardRenderEngine::disable_shadows() {
    if (_use_shadows) {
        teardown_shadows();
    }
    _use_shadows = false;
}

void StandardRenderEngine::setup_shadows()  {
    Renderer *shadow_renderer = new Renderer(SHADOW_HELPER_VERTEX_SHADER,
                                             SHADOW_HELPER_FRAGMENT_SHADER);
    _shadow_render_helper = new ShadowRenderHelper;
    _shadow_render_helper->set_shadow_renderer(shadow_renderer);
    for (unsigned i = 0; i < MAX_LIGHT_SOURCES; i++) {
        _shadow_screens[i] = new Screen();
        _shadow_screens[i]->set_render_engine(_shadow_render_helper);
    }
}
void StandardRenderEngine::teardown_shadows() {
    for (unsigned i = 0; i < MAX_LIGHT_SOURCES; i++) {
        delete _shadow_screens[i];
    }
    delete _shadow_render_helper->get_shadow_renderer();
    delete _shadow_render_helper;
}
void StandardRenderEngine::pre_render_shadows(std::vector<Light *> &lights) {
    if (! _use_shadows) return;
    for (unsigned i = 0; i < MAX_LIGHT_SOURCES && i < lights.size(); i++) {
        _shadow_screens[i]->set_world(_world);
        _shadow_screens[i]->set_viewpoint(lights[i]->get_viewpoint());
        _shadow_screens[i]->render();
    }
}

const int SHADOW_MAP_OFFSET = 1;

void StandardRenderEngine::configure_renderer_shadows(Renderer *renderer) {
    if (! _use_shadows) return;

    int mappings[MAX_LIGHT_SOURCES];
    for (unsigned i = 0; i < MAX_LIGHT_SOURCES; i++) {
        if (_use_lights[i] == 1) {
            glActiveTexture(GL_TEXTURE0 + SHADOW_MAP_OFFSET + i);
            _shadow_screens[i]->get_framebuffer()->get_depth_texture()->bind();
            mappings[i] = SHADOW_MAP_OFFSET + i;
        } else {
            mappings[i] = 0;
        }
    }
    renderer->set_uniform(std::string("shadow_map"), mappings, MAX_LIGHT_SOURCES);
        
}

void StandardRenderEngine::configure_object_shadow(Renderer *renderer, Renderable *renderable) {
    if (! _use_shadows) return;
    
    glm::mat4 shadow_mvp[MAX_LIGHT_SOURCES];
    for (unsigned i = 0; i < MAX_LIGHT_SOURCES; i++) {
        if (_use_lights[i] == 1) {
            shadow_mvp[i] = bias_matrix * _world->get_lights()[i]->get_viewpoint()->get_view_projection_matrix() * renderable->get_model_matrix();
        }
    }
    renderer->set_uniform(std::string("shadow_mvp"), shadow_mvp, MAX_LIGHT_SOURCES);
        
}

StandardRenderEngine::StandardRenderEngine() {
    _use_shadows = false;
}
        
StandardRenderEngine::~StandardRenderEngine() {
    if (_use_shadows) {
        teardown_shadows();
    }
}

void StandardRenderEngine::render(Viewpoint *viewpoint, World *world) {
    _world = world;
    _viewpoint = viewpoint;
    
    Renderable *current = nullptr;
    glm::vec3 light_direction;
    glm::mat4 view_matrix, projection_matrix;
    
    std::vector <Light *> lights = world->get_lights();
    std::set <Renderable *> renderables = world->get_renderables();

    pre_render_viewpoint(viewpoint);
    pre_render_lights(lights);
    pre_render_shadows(lights);
    
    for (std::set<Renderable *>::iterator it = renderables.begin();
         it != renderables.end(); it++) {
        current = *it;
        if (current->asset->get_textures()[0] != nullptr) {
            glActiveTexture(GL_TEXTURE0);
            current->asset->get_textures()[0]->bind();
        }
        
        current->asset->get_renderer()->bind();
        configure_renderer_viewpoint(current->asset->get_renderer());
        configure_renderer_lights(current->asset->get_renderer());
        configure_renderer_shadows(current->asset->get_renderer());
        
        configure_object_viewpoint(current->asset->get_renderer(), current);
        configure_object_shadow(current->asset->get_renderer(), current);
        current->asset->get_mesh()->bind();
        current->asset->get_mesh()->draw();
    }
}

void StandardRenderEngine::ShadowRenderHelper::render(Viewpoint *viewpoint, World *world) {
    _shadow_renderer->bind();
    std::set <Renderable *> renderables = world->get_renderables();
    for (std::set<Renderable *>::iterator it = renderables.begin();
         it != renderables.end(); it++) {
        Renderable *current = *it;
        
        _shadow_renderer->set_uniform("mvp", viewpoint->get_view_projection_matrix() * current->get_model_matrix());
        current->asset->get_mesh()->bind();
        current->asset->get_mesh()->draw();
    }
}

void StandardRenderEngine::ShadowRenderHelper::set_shadow_renderer(Renderer *renderer) {
    _shadow_renderer = renderer;
}

Renderer *StandardRenderEngine::ShadowRenderHelper::get_shadow_renderer() {
    return _shadow_renderer;
}