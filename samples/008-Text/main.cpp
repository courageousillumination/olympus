#include <iostream>

#include "olympus.hpp"
#include "utils/shortcuts.hpp"

using namespace std;
using namespace olympus;

Screen *screen = nullptr;

static void key_callback(Window *window, int key, int scancode, int action, int mods) {
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
    EasyWindow *easy_window = create_easy_window(640, 480);
    
    screen = easy_window->screen;
    
    Window *window = easy_window->window;
    window->set_keyboard_callback(key_callback);
    
    //Create an object to add to the world
    Renderer *renderer = new Renderer(TEXT_VERTEX_SHADER,
                                      TEXT_FRAGMENT_SHADER);
    
    FontAtlas *atlas = FontManager::get_instance().create_font_atlas("/usr/share/fonts/TTF/arial.ttf", 12);
    Text *text = new Text(renderer, atlas);
    text->set_text("Hello World!");
    /*Mesh *mesh = new Mesh(2, Mesh::TRIANGLES);
    mesh->set_vertex_attribute(0, 3, 6, g_vertex_buffer_data);
    mesh->set_vertex_attribute(1, 2, 6, texture_coords);
    
    //Create an asset to wrap all of the above
    Asset *asset = new Asset;
    asset->set_mesh(mesh);
    asset->set_renderer(renderer);
    
    Texture *texture = new Texture(Texture::TEXTURE_2D);
    texture->load_image("/home/tristan/development/olympus/samples/008-Text/texture.jpg");
    
    
    
    asset->add_texture(atlas->get_texture());
    */
    
    //Create a renderable to actually draw on the screen
    //Renderable *renderable = new Renderable;
    //renderable->asset = asset;
    //renderable->set_position(0.0f, 0.0f, 0.3f);
    
    easy_window->world->add_child(text);
    
    while(!window->get_should_close()) {
        window->render();
        window_manager.poll();
        fps::fps_tick();
    }
    
    destroy_easy_window(easy_window);
    
    //Clean up and exit
    Logger::shutdown();
    delete appender;
}
