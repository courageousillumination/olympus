#ifndef OLYMPUS__WINDOW__WINDOW_MANAGER
#define OLYMPUS__WINDOW__WINDOW_MANAGER

#include <vector>

#include "window.hpp"

#define DEFAULT_WINDOW_TITLE "Olympus"

namespace olympus {
    class WindowManager {
    private:
        std::vector<Window *> _windows;
        unsigned _num_windows;
        
        //Required for singleton design pattern
        WindowManager();
        WindowManager(WindowManager const&);
        void operator=(WindowManager const&);
        
        static void internal_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        std::vector<Window *> &get_windows() { return _windows; }
    public:
        /**
         * This function is mainly here for testing. It allows explicit initalization
         * of the backend framework.
         */
        void initialize_backend();
        /**
         * This function is mainly here for testing. It allows explicit destruction
         * of the backend framework.
         */
        void destroy_backend();
        
        /**
         * Retrieve the singelton instance of a window manager.
         */
        static WindowManager& get_instance();
        ~WindowManager();
        
        /**
         * Creates a window with the specified width and height
         */
        Window *create_window(unsigned width, unsigned height);
        /**
         * Creates a window with the specified width, height, and title
         */
        Window *create_window(unsigned width, unsigned height, const char *title);
        
        /**
         * Destroys a window and cleans up all resources associated with it
         */
        void destroy_window(Window *window);
        /**
         * Destroys all windows and all associated resources
         */
        void destroy_all_windows();
        
        unsigned get_num_windows() { return _num_windows; }
        
        /**
         * Triggers a poll of all events and will update all windows accordingly
         */
        void poll();
        
        /**
         * This function will simualte a keypress on a specific window. It should not
         * be used outside of testing/debugging.
         */
        void simulate_keypress(Window *window, int key, int scancode, int actions, int mods);
    };
}
#endif
