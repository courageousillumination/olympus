#ifndef OLYMPUS__RENDER__RENDER_ENGINE
#define OLYMPUS__RENDER__RENDER_ENGINE

#include <set>

#include "render/renderable.hpp"
#include "render/viewpoint.hpp"

namespace olympus {
    class RenderEngine {
    protected:
        std::set<Renderable *> _renderables;
    public:
        virtual ~RenderEngine() { }
        /**
         * The following two are used to add and remove renderables. These 
         * will generally be called by renderables when they are added to
         * the world.
         */
        virtual void add_renderable(Renderable *renderable);
        virtual void remove_renderable(Renderable *renderable);
        
        /**
         * This will perform the actual rendering, subclasses
         * must implement this method to specify how they want
         * to render the objects.
         */
        virtual void render(Viewpoint *viewpoint) = 0;
    };
}
#endif
