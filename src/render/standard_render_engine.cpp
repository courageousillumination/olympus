#include "debug/logger.hpp"

#include "render/world.hpp"
#include "render/renderable.hpp"
#include "render/light.hpp"
#include "render/screen.hpp"
#include "render/standard_render_engine.hpp"
#include "render/shaders.hpp"

using namespace olympus;

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
    if (lights.size() == 0) {
        _light_direction = glm::vec3(0, 0, 0);
    } else {
        glm::vec4 t = _view_matrix * glm::vec4((*lights.begin())->get_direction(), 0.0);
        _light_direction = glm::vec3(t[0], t[1], t[2]);
    }
}

void StandardRenderEngine::configure_renderer_lights(Renderer *renderer) {
    if (renderer->has_uniform(std::string("light_direction"))) {
        renderer->set_uniform(std::string("light_direction"), _light_direction);
    }
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
    for (unsigned i = 0; i < MAX_LIGHT_SOURCES && i < lights.size(); i++) {
        _shadow_screens[i]->set_world(_world);
        _shadow_screens[i]->set_viewpoint(lights[i]->get_viewpoint());
        _shadow_screens[i]->render();
    }
}

void StandardRenderEngine::configure_renderer_shadows(Renderer *renderer) {
    //TODO
}

StandardRenderEngine::StandardRenderEngine() {
    setup_shadows();
}
        
StandardRenderEngine::~StandardRenderEngine() {
    teardown_shadows();
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
            current->asset->get_textures()[0]->bind();
        }
        
        current->asset->get_renderer()->bind();
        configure_renderer_viewpoint(current->asset->get_renderer());
        configure_renderer_lights(current->asset->get_renderer());
        configure_renderer_shadows(current->asset->get_renderer());
        
        configure_object_viewpoint(current->asset->get_renderer(), current);
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