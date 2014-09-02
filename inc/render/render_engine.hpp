#ifndef OLYMPUS__RENDER__RENDER_ENGINE
#define OLYMPUS__RENDER__RENDER_ENGINE

#include <set>

#include "render/renderable.hpp"
#include "render/viewpoint.hpp"
#include "render/light.hpp"

#define MAX_LIGHT_SOURCES 1

namespace olympus {
    class World;
    
    class RenderEngine {
    protected:
        World *_world;
    public:
        virtual ~RenderEngine() { }
        void set_world(World *world);
        World *get_world();
        
        /**
         * This will perform the actual rendering, subclasses
         * must implement this method to specify how they want
         * to render the objects.
         */
        virtual void render(Viewpoint *viewpoint) = 0;
        
        
    };
}
#endif
