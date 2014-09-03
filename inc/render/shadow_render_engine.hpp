#ifndef OLYMPUS__RENDER__SHADOW_RENDER_ENGINE
#define OLYMPUS__RENDER__SHADOW_RENDER_ENGINE

#include "render/render_engine.hpp"
#include "render/screen.hpp"

namespace olympus {
    
    class ShadowRenderEngine : public RenderEngine {
    private:
        Screen *_shadow_screens[MAX_LIGHT_SOURCES];
        
        /**
         * This will render each shadow map.
         */
        class ShadowRenderEngineHelper : public RenderEngine {
        public:
            void render(Viewpoint *viewpoint, World *world);
        };
    public:
        ShadowRenderEngine();
        ~ShadowRenderEngine();
        void render(Viewpoint *viewpoint, World *world);
    };
}

#endif
