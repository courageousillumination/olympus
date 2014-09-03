#include <iostream>

#include "olympus.hpp"
#include "utils/shortcuts.hpp"

using namespace std;
using namespace olympus;

static const GLfloat cube_vertex_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

static GLfloat cube_colors[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

static GLfloat cube_normals[] = {
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    
};

Viewpoint *viewpoint = nullptr;
Light *light = nullptr;

static void key_callback(Window *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UP) {
        viewpoint->set_position(viewpoint->get_position() + glm::vec3(0.0, 0.0, -0.1));
    }
    if (key == GLFW_KEY_DOWN) {
        viewpoint->set_position(viewpoint->get_position() + glm::vec3(0.0, 0.0, 0.1));
    }
    if (key == GLFW_KEY_LEFT) {
        viewpoint->set_position(viewpoint->get_position() + glm::vec3(-0.1, 0.0, 0.0));
    }
    if (key == GLFW_KEY_RIGHT) {
        viewpoint->set_position(viewpoint->get_position() + glm::vec3(0.1, 0.0, 0.0));
    }
    if (key == GLFW_KEY_W) {
        viewpoint->set_orientation(viewpoint->get_orientation_euler() + glm::vec3(-0.1, 0.0, 0.0));
    }
    if (key == GLFW_KEY_S) {
        viewpoint->set_orientation(viewpoint->get_orientation_euler() + glm::vec3(0.1, 0.0, 0.0));
    }
    if (key == GLFW_KEY_A) {
        viewpoint->set_orientation(viewpoint->get_orientation_euler() + glm::vec3(0.0, -0.1, 0.0));
    }
    if (key == GLFW_KEY_D) {
        viewpoint->set_orientation(viewpoint->get_orientation_euler() + glm::vec3(0.0, 0.1, 0.0));
    }
    if (key == GLFW_KEY_H) {
        viewpoint->set_orientation(viewpoint->get_orientation_euler() + glm::vec3(0.0, 0.0, -0.1));
    }
    if (key == GLFW_KEY_J) {
        viewpoint->set_orientation(viewpoint->get_orientation_euler() + glm::vec3(0.0, 0.0, 0.1));
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
    Window *window = window_manager.create_window(640, 480);
    
    //Create a screen to attach to the window
    Screen *screen = new Screen;
    
    //Create a world to add to the screen
    World *world = new World;
    screen->set_world(world);
    
    //Create a render engine for the world
    StandardRenderEngine *render_engine = new StandardRenderEngine;
    screen->set_render_engine(render_engine);
    
    window->set_keyboard_callback(key_callback);
    
    //Create an object to add to the world
    Renderer *renderer = new Renderer(FLAT_LIGHT_VERTEX_SHADER,
                                      FLAT_LIGHT_FRAGMENT_SHADER);
    
    Mesh *mesh = new Mesh(3, Mesh::TRIANGLES);
    mesh->set_vertex_attribute(0, 3, 36, cube_vertex_data);
    mesh->set_vertex_attribute(1, 3, 36, cube_colors);
    mesh->set_vertex_attribute(2, 3, 36, cube_normals);
    
    //Create an asset to wrap all of the above
    Asset *asset = new Asset;
    asset->set_mesh(mesh);
    asset->set_renderer(renderer);
    
    //Create a renderable to actually draw on the screen
    Renderable *renderable1 = new Renderable;
    renderable1->asset = asset;
    renderable1->set_position(-3.0f, 0.0f, 0.0f);
    
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
    
    while(!window->should_close()) {
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
