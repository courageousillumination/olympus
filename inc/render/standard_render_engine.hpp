#ifndef OLYMPUS__RENDER__STANDARD_RENDER_ENGINE
#define OLYMPUS__RENDER__STANDARD_RENDER_ENGINE

#include "render/render_engine.hpp"

namespace olympus {
    /**
     * This will simply iterate over the renderables and render each
     * one using the given asset. It does not do any optimizations like
     * minimizing state change.
     */
    class StandardRenderEngine : public RenderEngine {
        void render(Viewpoint *viewpoint);
    };
}

#endif
