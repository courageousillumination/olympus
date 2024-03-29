#include <iostream>

#include "olympus.hpp"
#include "utils/shortcuts.hpp"

using namespace std;
using namespace olympus;


Viewpoint *viewpoint = nullptr;
Light *light = nullptr;
Screen *screen;

static void key_callback(Window *window, int key, int scancode, int action, int mods) {

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
    if (key == GLFW_KEY_Z and action == GLFW_PRESS) {
        screen->get_graphics_state()->wireframe = !screen->get_graphics_state()->wireframe ;
    }
    if (key == GLFW_KEY_ESCAPE) {
        window->set_should_close(true);
    }
}

int main() {
    //Set up debug and info logging
    StreamAppender *appender = new StreamAppender(Logger::DEBUG | Logger::INFO, std::cout);
    Logger::add_appender(appender);
    fps::enable_fps_logging(true);
    
    //Create a window
    WindowManager &window_manager = WindowManager::get_instance();
    Window *window = window_manager.create_window(640, 480);
    
    //Create a screen to attach to the window
    screen = new Screen(640, 480);
    //screen->get_graphics_state()->cull = true;
    
    //Create a world to add to the screen
    World *world = new World;
    screen->set_world(world);
    
    //Create a render engine for the world
    StandardRenderEngine *render_engine = new StandardRenderEngine;
    screen->set_render_engine(render_engine);
    render_engine->enable_lighting();
    render_engine->enable_shadows();
    
    window->set_keyboard_callback(key_callback);
    
    //Create an object to add to the world
    Renderer *renderer = new Renderer(SHADOW_VERTEX_SHADER,
                                      SHADOW_FRAGMENT_SHADER);
    
    Terrain *terrain = new Terrain(renderer);
    terrain->set_scale(5.0f, 5.0f, 5.0f);
    terrain->set_position(-2.5f, -2.5f, 0.0f);
    
    world->add_child(terrain);
    
    //Set up the viewpoint
    viewpoint = new Viewpoint;
    viewpoint->set_far(100.0f);
    viewpoint->set_near(0.1f);
    viewpoint->set_position(0.0f, 0.0f, 2.0f);
    screen->set_viewpoint(viewpoint);
    
    //Create a new directional Light for the screen
    light = new Light(Light::DIRECTIONAL);
    light->set_direction(1.0f, -1.0f, 0.0f);
    light->set_shadow_box(glm::vec2(-6, 6),
                          glm::vec2(-6, 6),
                          glm::vec2(-6, 6));
    world->add_child(light);
    
    //DEBUG
    //Screen *shadow_screen = render_engine->get_shadow_screens()[0];
    //window->add_screen(shadow_screen, 0.0f, 0.0f, 1.0f, 1.0f);
    window->add_screen(screen);
    
    while(!window->get_should_close()) {
        window->render();
        window_manager.poll();
        fps::fps_tick();
    }
    
    delete light;
    delete viewpoint;
    delete terrain;
    delete renderer;
    delete world;
    delete screen;
    delete render_engine;
    
    window_manager.destroy_all_windows();
    
    // Make sure we've cleaned everything up.
    ResourceManager::get_instance().check_allocation();
    //Clean up and exit
    Logger::shutdown();
    delete appender;
}
