#include <iostream>



#include "olympus.hpp"
#include "utils/shortcuts.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace olympus;

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

static GLfloat cube_colors[] = {
    // front
    0.0, 0.0, 1.0,
    1.0, 0.0, 0.0,
    1.0, 1.0, 0.0
};

static GLfloat cube_normals[] = {
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0
};

Viewpoint *viewpoint = nullptr;
Light *light = nullptr;

static void key_callback(Window *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS && action != GLFW_REPEAT) { return; }
    if (key == GLFW_KEY_UP) {
        viewpoint->set_position(viewpoint->get_position() + glm::vec3(0.0, 0.0, -0.1) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_DOWN) {
        viewpoint->set_position(viewpoint->get_position() + glm::vec3(0.0, 0.0, 0.1) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_LEFT) {
        viewpoint->set_position(viewpoint->get_position() + glm::vec3(-0.1, 0.0, 0.0) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_RIGHT) {
        viewpoint->set_position(viewpoint->get_position() + glm::vec3(0.1, 0.0, 0.0) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_W) {
        viewpoint->set_orientation(glm::angleAxis(-0.1f, glm::vec3(1, 0, 0)) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_S) {
        viewpoint->set_orientation(glm::angleAxis(0.1f, glm::vec3(1, 0, 0)) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_A) {
        viewpoint->set_orientation(glm::angleAxis(-0.1f, glm::vec3(0, 1, 0)) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_D) {
        viewpoint->set_orientation(glm::angleAxis(0.1f, glm::vec3(0, 1, 0)) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_H) {
        viewpoint->set_orientation(glm::angleAxis(-0.1f, glm::vec3(0, 0, 1)) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_J) {
        viewpoint->set_orientation(glm::angleAxis(0.1f, glm::vec3(0, 0, 1)) * viewpoint->get_orientation());
    }
    if (key == GLFW_KEY_I) {
        light->set_direction(light->get_direction() + glm::vec3(0.1, 0.0, 0.0));
    }
    if (key == GLFW_KEY_K) {
        light->set_direction(light->get_direction() + glm::vec3(-0.1, 0.0, 0.0));
    }
    if (key == GLFW_KEY_ESCAPE) {
        window->set_should_close(true);
    }
}

int main() {
    //Set up debug and info logging
    StreamAppender *appender = new StreamAppender(std::cout);
    Logger::set_appender(appender);
    Logger::set_level(Logger::DEBUG | Logger::INFO);
    fps::enable_fps_logging(true);
    
    //Create a window
    WindowManager &window_manager = WindowManager::get_instance();
    EasyWindow *easy_window = create_easy_window(640, 480);
    
    Window *window = easy_window->window;
    window->set_keyboard_callback(key_callback);
    
    //Create an object to add to the world
    Renderer *renderer = new Renderer(FLAT_LIGHT_VERTEX_SHADER,
                                      FLAT_LIGHT_FRAGMENT_SHADER);
    
    Mesh *mesh = new Mesh(3, Mesh::TRIANGLES);
    mesh->set_vertex_attribute(0, 3, 3, g_vertex_buffer_data);
    mesh->set_vertex_attribute(1, 3, 3, cube_colors);
    mesh->set_vertex_attribute(2, 3, 3, cube_normals);
    
    //Create an asset to wrap all of the above
    Asset *asset = new Asset;
    asset->set_mesh(mesh);
    asset->set_renderer(renderer);
    
    //Create a renderable to actually draw on the screen
    Renderable *renderable = new Renderable;
    renderable->asset = asset;
    renderable->set_position(0.0f, 0.0f, 0.3f);
    
    easy_window->world->add_child(renderable);
     
    //Set up the viewpoint
    viewpoint = new Viewpoint;
    viewpoint->set_far(100.0f);
    viewpoint->set_near(1.0f);
    viewpoint->set_position(0.0f, 0.0f, 2.0f);
    easy_window->screen->set_viewpoint(viewpoint);
    
    //Create a new directional Light for the screen
    light = new Light(Light::DIRECTIONAL);
    light->set_direction(0.0f, 0.0f, -1.0f);
    easy_window->world->add_child(light);
    
    while(!window->should_close()) {
        window->render();
        window_manager.poll();
        fps::fps_tick();
    }
    
    delete light;
    
    destroy_easy_window(easy_window);
    delete viewpoint;
    
    //Clean up and exit
    Logger::shutdown();
    delete appender;
}
