#ifndef OLYMPUS__RENDER__RENDER_ENGINE
#define OLYMPUS__RENDER__RENDER_ENGINE

#include <set>

#include "world/viewpoint.hpp"

#define MAX_LIGHT_SOURCES 2

namespace olympus {
    class World;
    
    class RenderEngine {
    public:
        virtual ~RenderEngine() { }
        
        /**
         * This will perform the actual rendering, subclasses
         * must implement this method to specify how they want
         * to render the objects.
         */
        virtual void render(Viewpoint *viewpoint, World *world) = 0;
        
        
    };
}
#endif
