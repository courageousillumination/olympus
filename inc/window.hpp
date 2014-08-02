#ifndef OLYMPUS__WINDOW
#define OLYMPUS__WINDOW

#include <GLFW/glfw3.h>

namespace olympus {
    class WindowManager;
    
    class Window {
    private:
        GLFWwindow *_internal_window;
        
        unsigned  _width, _height;
       
        Window(unsigned width, unsigned height, const char *title);
    public:
        ~Window();
        
        unsigned get_width() { return _width; }
        unsigned get_height() { return _height; }
        
        void set_height(unsigned height);
        void set_width(unsigned width);
        void set_dimensions(unsigned width, unsigned height);
        
        friend WindowManager;
    };
}
#endif
