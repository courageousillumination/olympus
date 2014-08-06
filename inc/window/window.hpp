#ifndef OLYMPUS__WINDOW__WINDOW
#define OLYMPUS__WINDOW__WINDOW

#include <GLFW/glfw3.h>

#include "render/screen.hpp"

namespace olympus {
    class WindowManager;
    
    class Window {
    private:
        GLFWwindow *_internal_window;
        
        unsigned  _width, _height;
       
        Window(unsigned width, unsigned height, const char *title);
        
        void (* _key_callback)(Window *, int, int, int, int);
        
        //TODO: Allow a window to have multiple screens.
        Screen *_screen;
    public:
        ~Window();
        
        /**
         * Renders the current scene using all attached screens
         */
        void render();
        
        unsigned get_width() { return _width; }
        unsigned get_height() { return _height; }
        
        bool should_close();
        void set_should_close(bool flag);
        
        void set_height(unsigned height);
        void set_width(unsigned width);
        void set_dimensions(unsigned width, unsigned height);
        
        void set_keyboard_callback(void (* callback)(Window *, int, int, int, int));
        
        friend WindowManager;
    };
}
#endif
