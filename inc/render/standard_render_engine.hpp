#ifndef OLYMPUS__RENDER__STANDARD_RENDER_ENGINE
#define OLYMPUS__RENDER__STANDARD_RENDER_ENGINE

#include "render/render_engine.hpp"

namespace olympus {
    class Screen;
    
    /**
     * This will simply iterate over the renderables and render each
     * one using the given asset. It does not do any optimizations like
     * minimizing state change.
     */
    class StandardRenderEngine : public RenderEngine {
    private:
        World *_world;
        Viewpoint *_viewpoint;
        
        /**
         * Here we follow the following convention for new features:
         *      * Anything that needs to be setup and torn down should be in a 
         *        setup_{name}/teardown_{name} pair. These will be called during the
         *        construction of the render engine.
         *      * Anything that can be done once per render loop should be done in a
         *        pre_render_{name} function. This can update local state, etc. 
         *      * Anything that needs to be done once per shader should happen in a 
         *        configure_renderer_{name} function. This should take in a Renderer and
         *        ideally this shouldn't need to update any local state.
         *      * Anything else should use a configure_object_{name} function.
         */
        //Things need to support viewpoints
        void pre_render_viewpoint(Viewpoint *viewpoint);
        void configure_renderer_viewpoint(Renderer *renderer);
        void configure_object_viewpoint(Renderer *renderer, Renderable *renderable);
        
        glm::mat4 _view_matrix;
        glm::mat4 _projection_matrix;
        
        //Things need to support lights
        void pre_render_lights(std::vector<Light *> &lights);
        void configure_renderer_lights(Renderer *renderer);
        
        glm::vec3 _light_directions[MAX_LIGHT_SOURCES];
        int _use_lights[MAX_LIGHT_SOURCES];
        
        //Things needed to support shadows
        void setup_shadows();
        void teardown_shadows();
        void pre_render_shadows(std::vector<Light *> &lights);
        void configure_renderer_shadows(Renderer *renderer);
        void configure_object_shadow(Renderer *renderer, Renderable *renderable);
        
        class ShadowRenderHelper : public RenderEngine {
        private:
            Renderer *_shadow_renderer;
        public:
            void set_shadow_renderer(Renderer *renderer);
            Renderer *get_shadow_renderer();
            void render(Viewpoint *viewpoint, World *world);
        };
        
        ShadowRenderHelper *_shadow_render_helper;
        Screen *_shadow_screens[MAX_LIGHT_SOURCES];
        bool _use_shadows;
    public:
        StandardRenderEngine();
        ~StandardRenderEngine();
        
        void enable_shadows();
        void disable_shadows();
        
        void render(Viewpoint *viewpoint, World *world);
        
        //DEBUG FUNCTIONS
        Screen **get_shadow_screens() { return _shadow_screens; }
    };
}

#endif
