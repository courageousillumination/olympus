#ifndef OLYMPUS__WINDOW
#define OLYMPUS__WINDOW

namespace olympus {
    class WindowManager;
    
    class Window {
    private:
       unsigned  _width, _height;
       
       Window(unsigned width, unsigned height, const char *title);
    public:
        unsigned get_width() { return _width; }
        unsigned get_height() { return _height; }
        
        friend WindowManager;
    };
}
#endif
