#ifndef OLYMPUS__DEBUG__FPS
#define OLYMPUS__DEBUG__FPS
namespace olympus {
    /**
     * This is a simple namspace to allow for logging fps. It will
     * simply keep a counter and print it out every second at the
     * debug level.
     * NOTE: This is not threadsafe.
     */
    namespace fps {
        void enable_fps_logging(bool flag);
        /**
         * This will always update the fps counter. If fps logging 
         * has been enabled then this will log it out every 0.5
         * seconds.
         */
        void fps_tick();
        
        /**
         * This will get the current fps averaged over the last second.
         */
        double get_fps();
    }
}
#endif
