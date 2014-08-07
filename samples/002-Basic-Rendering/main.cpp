#include <iostream>

#include "olympus.hpp"

using namespace std;
using namespace olympus;

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

static GLfloat cube_texcoords[] = {
    // front
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0
};

static void key_callback(Window *window, int key, int scancode, int action, int mods) {
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
    window->set_keyboard_callback(key_callback);
    
    //Create a screen to attach to the window
    Screen *screen = new Screen;
    window->add_screen(screen);
    
    //Create a world to add to the screen
    World *world = new World;
    screen->set_world(world);
    
    //Create a render engine for the world
    RenderEngine *render_engine = new StandardRenderEngine;
    world->set_render_engine(render_engine);
   
    //Create an object to add to the world
    Texture *texture = new Texture(Texture::TEXTURE_2D);
    texture->load_image("/home/tristan/Development/olympus/texture.jpg");
    Renderer *renderer = new Renderer(TEXTURE_VERTEX_SHADER,
                            TEXTURE_FRAGMENT_SHADER);
    
    Mesh *mesh = new Mesh(2, Mesh::TRIANGLES);
    mesh->set_vertex_attribute(0, 3, 3, g_vertex_buffer_data);
    mesh->set_vertex_attribute(1, 2, 3, cube_texcoords);
    
    //Create an asset to wrap all of the above
    Asset *asset = new Asset;
    asset->set_mesh(mesh);
    asset->set_renderer(renderer);
    asset->add_texture(texture);
    
    //Create a renderable to actually draw on the screen
    Renderable *renderable = new Renderable;
    renderable->asset = asset;
    
    world->add_child(renderable);
    
    while(!window->should_close()) {
        window->render();
        window_manager.poll();
        fps::fps_tick();
    }
    
    //Clean up and exit
    Logger::shutdown();
    delete appender;
}