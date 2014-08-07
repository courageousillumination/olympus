#ifndef OLYMPUS__RENDER__WORLD
#define OLYMPUS__RENDER__WORLD

#include "render/render_engine.hpp"
#include "render/world_object.hpp"

namespace olympus {
    class World : public WorldObject {
    private:
        RenderEngine *_render_engine;
    public:
        World();
        RenderEngine *get_render_engine();
    };
}
#endif
