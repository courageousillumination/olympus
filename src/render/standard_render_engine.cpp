#include "debug/logger.hpp"

#include "render/standard_render_engine.hpp"

using namespace olympus;

void StandardRenderEngine::render(Viewpoint *viewpoint) {
    Renderable *current = nullptr;
    //Pull out VP matricies
    glm::mat4 view_matrix, projection_matrix;
    if (viewpoint == nullptr) {
        view_matrix = glm::mat4(1.0f);
        projection_matrix = glm::mat4(1.0f); 
    }
    else {
        view_matrix = viewpoint->get_view_matrix();
        projection_matrix = viewpoint->get_projection_matrix();
    }
    for (std::set<Renderable *>::iterator it = _renderables.begin();
         it != _renderables.end(); it++) {
        current = *it;
        if (current->asset->get_textures()[0] != nullptr) {
            current->asset->get_textures()[0]->bind();
        }
        
        current->asset->get_renderer()->bind();
        current->asset->get_renderer()->set_uniform(std::string("model_view_matrix"), view_matrix * current->get_model_matrix());
        current->asset->get_renderer()->set_uniform(std::string("projection_matrix"), projection_matrix);
        
        current->asset->get_mesh()->bind();
        current->asset->get_mesh()->draw();
    }
}