#ifndef OLYMPUS__WINDOW__WINDOW_MANAGER
#define OLYMPUS__WINDOW__WINDOW_MANAGER

#include <vector>

#include "window.hpp"

#define DEFAULT_WINDOW_TITLE "Olympus-Window"

namespace olympus {
    class WindowManager {
    private:
        std::vector<Window *> _windows;

        
        // Required for singleton design pattern; the last two will not be implemented.
        WindowManager();
        WindowManager(WindowManager const&);
        void operator=(WindowManager const&);
        
        /**
         * These two functions exist to work around the ickyness that is GLFW and callbacks.
         * The first function is a static function that is registered as the GLFW_keycallback for all 
         * windows created by this manager. The second allows that static method to get the list of windows
         * out of the singleton manager. It then finds the Window that is associated with the GLFWwindow and
         * calls the callback on that. 
         */
        static void internal_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        std::vector<Window *> &get_windows() { return _windows; }
    public:
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
        
        /**
         * Triggers a poll of all events. This will update windows, call callbacks, and
         * anything else that could be triggered by an external event.
         */
        void poll();
        
        unsigned get_num_windows() { return _windows.size(); }
        
        /**
         * TESTING: Simulates a keypress to a given window.
         */
        void simulate_keypress(Window *window, int key, int scancode, int actions, int mods);
        
        /**
         * TESTING. Allow explicit initialization of the backend (GLFW).
         */
        void initialize_backend();
        
        /**
         * TESTING: Allows explicit destruction of the backend (GLFW).
         */
        void destroy_backend();
    };
}
#endif
