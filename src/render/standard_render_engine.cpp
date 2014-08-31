#include "debug/logger.hpp"

#include "render/standard_render_engine.hpp"

using namespace olympus;

void StandardRenderEngine::render(Viewpoint *viewpoint) {
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
    }
}