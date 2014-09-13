#include <iostream>

#include "olympus.hpp"
#include "utils/shortcuts.hpp"

using namespace std;
using namespace olympus;

static const glm::vec3 cube_vertex_data[] = {
    //Front
    glm::vec3(-1.0, -1.0,  1.0),
    glm::vec3(1.0, -1.0,  1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    glm::vec3(-1.0, -1.0,  1.0),
    glm::vec3(-1.0,  1.0,  1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    //Left
    glm::vec3(-1.0, -1.0,  -1.0),
    glm::vec3(-1.0, -1.0,  1.0),
    glm::vec3(-1.0,  1.0,  1.0),
    
    glm::vec3(-1.0, -1.0,  -1.0),
    glm::vec3(-1.0,  1.0,  -1.0),
    glm::vec3(-1.0,  1.0,  1.0),
    
    //Right
    glm::vec3(1.0, -1.0,  -1.0),
    glm::vec3(1.0, -1.0,  1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    glm::vec3(1.0, -1.0,  -1.0),
    glm::vec3(1.0,  1.0,  -1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    //Back
    glm::vec3(-1.0, -1.0,  -1.0),
    glm::vec3(1.0, -1.0,  -1.0),
    glm::vec3(1.0,  1.0,  -1.0),
    
    glm::vec3(-1.0, -1.0,  -1.0),
    glm::vec3(-1.0,  1.0,  -1.0),
    glm::vec3(1.0,  1.0,  -1.0),
    
    //Top
    glm::vec3(-1.0, 1.0,  -1.0),
    glm::vec3(1.0, 1.0,  -1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    glm::vec3(-1.0, 1.0,  -1.0),
    glm::vec3(-1.0,  1.0,  1.0),
    glm::vec3(1.0,  1.0,  1.0),
    
    //Bottom
    glm::vec3(-1.0, -1.0, -1.0),
    glm::vec3(1.0, -1.0, -1.0),
    glm::vec3(1.0,  -1.0, 1.0),
    
    glm::vec3(-1.0, -1.0, -1.0),
    glm::vec3(-1.0,  -1.0, 1.0),
    glm::vec3(1.0,  -1.0, 1.0),
};


static glm::vec3 cube_color_data[] = {
    glm::vec3(0.0, 0.0, 1.0),
    glm::vec3(0.0, 0.0, 1.0),
    glm::vec3(0.0, 0.0, 1.0),
    glm::vec3(0.0, 0.0, 1.0),
    
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    
    glm::vec3(0.0, 0.0, 1.0),
    glm::vec3(0.0, 0.0, 1.0),
    glm::vec3(0.0, 0.0, 1.0),
    glm::vec3(0.0, 0.0, 1.0),
    
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    glm::vec3(1.0, 0.0, 0.0),
    
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    glm::vec3(0.0, 1.0, 0.0),
    
};

static glm::vec3 cube_normals[] = {
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    glm::vec3(0, 0, 1.0),
    
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    glm::vec3(-1.0, 0, 0),
    
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    glm::vec3(1.0, 0, 0),
    
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    glm::vec3(0, 0, -1.0),
    
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    glm::vec3(0, 1.0, 0.0),
    
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
    glm::vec3(0, -1.0, 0.0),
};

Viewpoint *viewpoint = nullptr;
Light *light = nullptr;

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
    Screen *screen = new Screen;
    
    //Create a world to add to the screen
    World *world = new World;
    screen->set_world(world);
    
    //Create a render engine for the world
    StandardRenderEngine *render_engine = new StandardRenderEngine;
    screen->set_render_engine(render_engine);
    render_engine->enable_shadows();
    
    window->set_keyboard_callback(key_callback);
    
    //Create an object to add to the world
    Renderer *renderer = new Renderer(SHADOW_VERTEX_SHADER,
                                      SHADOW_FRAGMENT_SHADER);
    
    Mesh *mesh = new Mesh(3, Mesh::TRIANGLES);
    mesh->set_vertex_attribute(0, 3, 36, (float *)cube_vertex_data);
    mesh->set_vertex_attribute(1, 3, 36, (float *)cube_color_data);
    mesh->set_vertex_attribute(2, 3, 36, (float *)cube_normals);
    
    //Create an asset to wrap all of the above
    Asset *asset = new Asset;
    asset->set_mesh(mesh);
    asset->set_renderer(renderer);
    
    //Create a renderable to actually draw on the screen
    Renderable *renderable1 = new Renderable;
    renderable1->asset = asset;
    renderable1->set_position(0.0f, 0.0f, 0.0f);
    
    world->add_child(renderable1);
    
    
    Renderable *renderable2 = new Renderable;
    renderable2->asset = asset;
    renderable2->set_position(0.0f, 0.0f, 3.0f);
    
    world->add_child(renderable2);
    
    //Set up the viewpoint
    viewpoint = new Viewpoint;
    viewpoint->set_far(100.0f);
    viewpoint->set_near(1.0f);
    viewpoint->set_position(0.0f, 0.0f, 2.0f);
    screen->set_viewpoint(viewpoint);
    
    //Create a new directional Light for the screen
    light = new Light(Light::DIRECTIONAL);
    light->set_direction(0.0f, 0.0f, -1.0f);
    world->add_child(light);
    
    //DEBUG
    Screen *shadow_screen = render_engine->get_shadow_screens()[0];
    window->add_screen(shadow_screen, 0.0f, 0.0f, 1.0f, 1.0f);
    window->add_screen(screen);
    
    while(!window->get_should_close()) {
        window->render();
        window_manager.poll();
        fps::fps_tick();
    }
    
    delete light;
    delete viewpoint;
    
    //Clean up and exit
    Logger::shutdown();
    delete appender;
}
