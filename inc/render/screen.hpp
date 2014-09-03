#ifndef OLYMPUS__RENDER__SCREEN
#define OLYMPUS__RENDER__SCREEN

#include "render/framebuffer.hpp"
#include "render/viewpoint.hpp"
#include "render/world.hpp"
#include "render/renderer.hpp"
#include "render/render_engine.hpp"

namespace olympus {
    /**
     * A screen represents a virtual window. It can be attached to
     * a physical window, or used for offscreen rendering. This is
     * essentially a collection of a world, a viewpoint and a 
     * render engine. 
     */
    class Screen {
    private:
        Viewpoint *_viewpoint;
        World *_world;
        Framebuffer *_framebuffer;
        RenderEngine *_render_engine;
    public:
        Screen();
        ~Screen();
        
        /**
         * This does the actual render, using the current world and viewpoint.
         * NOTE: This will be rendered to a framebuffer (texture?) which others
         * will have to grab.
         */
        void render();

        /**
         * Every Screen can have a viewpoint which defines how it will look
         * at the world.
         */
        void set_viewpoint(Viewpoint *viewpoint);
        /**
         * Each Screen can have a single world which it will render
         */
        void set_world(World *world);
        
        void set_render_engine(RenderEngine *render_engine);
        
        Viewpoint *get_viewpoint();
        World *get_world();        
        Framebuffer *get_framebuffer();
        RenderEngine *get_render_engine();
    };
}
#endif
