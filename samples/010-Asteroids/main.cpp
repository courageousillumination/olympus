#include <iostream>
#include <cstdlib>


#include "olympus.hpp"
#include "utils/shortcuts.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace olympus;


unsigned NUM_ASTEROIDS = 1000;

Viewpoint *viewpoint = nullptr;
EasyWindow *easy_window = nullptr;

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
    if (key == GLFW_KEY_Z and action == GLFW_PRESS) {
        easy_window->screen->get_graphics_state()->wireframe = !easy_window->screen->get_graphics_state()->wireframe ;
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
    easy_window = create_easy_window(640, 480);

    Window *window = easy_window->window;
    window->set_keyboard_callback(key_callback);

    //Create an object to add to the world
    Renderer *renderer = new Renderer(FLAT_VERTEX_SHADER,
                                      FLAT_FRAGMENT_SHADER);

    // Mesh *mesh = create_uv_sphere(1.0, 30, 30);


    //Draw n asteroids on the screen
    for(unsigned i = 0; i < NUM_ASTEROIDS; i++) {
        Mesh *mesh = create_icosphere(1.0, 3);

        //Create an asset to wrap all of the above
        Asset *asset = new Asset;
        asset->set_mesh(mesh);
        asset->set_renderer(renderer);

        Renderable *renderable = new Renderable;
        renderable->asset = asset;
        renderable->set_position(std::rand() % 200 - 100, std::rand() % 200 - 100, std::rand() % 200 - 100);
        renderable->set_scale(0.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0 - 0.5))),
                              0.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0 - 0.5))),
                              0.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2.0 - 0.5))));
        easy_window->world->add_child(renderable);
    }

    //Set up the viewpoint
    viewpoint = new Viewpoint;
    viewpoint->set_far(100.0f);
    viewpoint->set_near(1.0f);
    viewpoint->set_position(0.0f, 0.0f, 2.0f);
    easy_window->screen->set_viewpoint(viewpoint);

    while(!window->get_should_close()) {
        window->render();
        window_manager.poll();
        fps::fps_tick();
    }

    destroy_easy_window(easy_window);
    delete viewpoint;

    //Clean up and exit
    Logger::shutdown();
    delete appender;
}
