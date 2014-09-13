#ifndef OLYMPUS__WINDOW__WINDOW
#define OLYMPUS__WINDOW__WINDOW

#include <vector>

#include <GLFW/glfw3.h>

#include "render/screen.hpp"
#include "render/graphics_state_manager.hpp"

namespace olympus {
    class WindowManager;
    
    /**
     * A window represents a window in the windo manager. This class generally
     * wraps the underlying GLFW calls and makes things a little more OOP. A window
     * can have multiple Screens positioned at arbitrary points on the window.
     * Windows can also have callbacks set on them, but these will not trigger until
     * the window manager polls for events.
     */
    class Window {
    private:
        /**
         * A simple structure used to store a screen and mesh pair. We need 
         * these to render the screens to the window.
         */
        struct ScreenAndMesh {
            Screen *screen;
            Mesh *mesh;
        };
        
        unsigned  _width, _height;
        
        // A simpler renderer that can render the textures produced by screens
        // to the window.
        Renderer *_renderer;
        GraphicsState *_graphics_state;
        GLFWwindow *_internal_window;
        
        std::vector<ScreenAndMesh> _screens;
 
        // Stores a function pointer to the callback for any keyboard event
        void (* _key_callback)(Window *, int, int, int, int);
        
        // Private so only the window manager can construct windows
        Window(unsigned width, unsigned height, const char *title);
    public:
        ~Window();
        
        /**
         * Renders the current scene using all attached screens
         */
        void render();

        /**
         * Adds a keyboard callback to the current window. These will only be
         * called when the window manager polls for input.
         */
        void set_keyboard_callback(void (* callback)(Window *, int, int, int, int));
        
        /**
         * Each screen is defined in terms of x, y, width and height on a -1.0 to 1.0
         * scale. Adding a single screen is simply a short cut for creating a screen
         * that takes up the entire window.
         */
        void add_screen(Screen *screen);
        void add_screen(Screen *screen, float x, float y, float width, float height);
        void remove_screen(Screen *screen);        
        
        // Getters and Setters
        
        void set_height(unsigned height);
        void set_width(unsigned width);
        void set_dimensions(unsigned width, unsigned height);
        void set_should_close(bool flag);

        unsigned get_width() { return _width; }
        unsigned get_height() { return _height; }
        bool get_should_close();
        GraphicsState *get_graphics_state();
        
        friend WindowManager;
    };
}
#endif
