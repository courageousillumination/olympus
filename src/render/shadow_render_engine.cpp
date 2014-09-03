#include "debug/logger.hpp"

#include "render/shadow_render_engine.hpp"


using namespace olympus;

/**
 * The outline is something like this:
 * 
 * 1) For each light source create a seperate screen. This screen has the
 * viewpoint of the light, a ShadowRenderEngineHelper render_engine and
 * the world that is associated with the parent.
 * 
 * 2) When we call render on ShadowRenderEngine we loop over all valid light
 * sources and render the specified screen. 
 * 
 * 3) Bind all the textures from all shadow screens. 
 * 
 * 4) Render the main scene.
 */

void ShadowRenderEngine::ShadowRenderEngineHelper::render(Viewpoint *viewpoint, World *world) {
    
}

ShadowRenderEngine::ShadowRenderEngine() {
    ShadowRenderEngineHelper *helper = new ShadowRenderEngineHelper;
    for (unsigned i = 0; i < MAX_LIGHT_SOURCES; i++) {
        _shadow_screens[i] = new Screen();
        _shadow_screens[i]->set_render_engine(helper);
    }
}

ShadowRenderEngine::~ShadowRenderEngine() {
    for (unsigned i = 0; i < MAX_LIGHT_SOURCES; i++) {
        delete _shadow_screens[i];
    }
}

void ShadowRenderEngine::render(Viewpoint *viewpoint, World *world) {
    std::vector <Light *> lights = world->get_lights();
    std::set <Renderable *> renderables = world->get_renderables();
     
    //First we render all the shadow maps
    for (unsigned i = 0; i < lights.size(); i++) {
        _shadow_screens[i]->set_viewpoint(lights[i]->get_viewpoint());
        _shadow_screens[i]->set_world(world);
        _shadow_screens[i]->render();
    }
    
    //Then we render our scene, binding all the shadow maps.
    
    
    /*
    Renderable *current = nullptr;
    glm::vec3 light_direction;
    glm::mat4 view_matrix, projection_matrix;

    if (viewpoint == nullptr) {
        view_matrix = glm::mat4(1.0f);
        projection_matrix = glm::mat4(1.0f); 
    } else {
        view_matrix = viewpoint->get_view_matrix();
        projection_matrix = viewpoint->get_projection_matrix();
    }
    
    if (_lights.size() == 0) {
        light_direction = glm::vec3(0, 0, 0);
    } else {
        glm::vec4 t = view_matrix * glm::vec4((*_lights.begin())->get_direction(), 0.0);
        light_direction = glm::vec3(t[0], t[1], t[2]);
    }
    
    for (std::set<Renderable *>::iterator it = _renderables.begin();
         it != _renderables.end(); it++) {
        current = *it;
        if (current->asset->get_textures()[0] != nullptr) {
            current->asset->get_textures()[0]->bind();
        }
        
        current->asset->get_renderer()->bind();
        
        if (current->asset->get_renderer()->has_uniform(std::string("light_direction"))) {
            current->asset->get_renderer()->set_uniform(std::string("light_direction"), light_direction);
        }
        current->asset->get_renderer()->set_uniform(std::string("model_view_matrix"), view_matrix * current->get_model_matrix());
        current->asset->get_renderer()->set_uniform(std::string("projection_matrix"), projection_matrix);
        
        current->asset->get_mesh()->bind();
        current->asset->get_mesh()->draw();
    }*/
}