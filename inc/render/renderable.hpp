#ifndef OLYMPUS__RENDER__RENDERABLE
#define OLYMPUS__RENDER__RENDERABLE

#include "render/world_object.hpp"
#include "render/asset.hpp"

namespace olympus {
    /**
     * A renderable is any world object that has an asset associated
     * with it.
     */
    struct Renderable : public WorldObject {
        Asset *asset;
    protected:
        void set_parent(WorldObject *parent);
    };
}
#endif
