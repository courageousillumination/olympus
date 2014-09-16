#ifndef OLYMPUS__RENDER__SCREEN
#define OLYMPUS__RENDER__SCREEN

#include "render/framebuffer.hpp"
#include "render/renderer.hpp"
#include "render/render_engine.hpp"
#include "render/graphics_state_manager.hpp"

#include "world/world.hpp"
#include "world/viewpoint.hpp"

namespace olympus {
    /**
     * A screen represents a virtual window. It can be attached to
     * a Window, or used for offscreen rendering. It is essentially
     * a collection of a viewpoint, world, graphics_state and render_engine
     * and acts as glue between all of them.
     */
    class Screen {
    private:
        // The first three can be set by other callers; the last two 
        // are owned by the screen and can be grabbed, but can't be changed
        Viewpoint *_viewpoint;
        World *_world;
        RenderEngine *_render_engine;
        Framebuffer *_framebuffer;
        GraphicsState *_graphics_state;
        
        Texture *_color_texture;
        Texture *_depth_texture;
    public:
        Screen(unsigned width, unsigned height);
        ~Screen();
        
        /**
         * This does the actual render, using the current world and viewpoint.
         * NOTE: This will be rendered to a framebuffer which others
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
        
        /**
         * Different screens can use different render engines to affect how
         * the world appears.
         */
        void set_render_engine(RenderEngine *render_engine);
        
        Viewpoint *get_viewpoint();
        World *get_world();        
        RenderEngine *get_render_engine();
        Framebuffer *get_framebuffer();
        GraphicsState *get_graphics_state();
    };
}
#endif
