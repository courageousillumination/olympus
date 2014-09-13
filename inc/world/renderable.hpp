#ifndef OLYMPUS__WORLD__RENDERABLE
#define OLYMPUS__WORLD__RENDERABLE

#include "world/world_object.hpp"
#include "render/asset.hpp"

namespace olympus {
    /**
     * A renderable is a WorldObject that has an asset associated with it.
     * In addition to holding the asset it will register itself with 
     * the root whenever it is added to a new world.
     */
    struct Renderable : public WorldObject {
        Asset *asset;
    protected:
        /**
         * In addition to setting the parent, we must make sure we're properly
         * registered in the roots renderable set.
         */
        void set_parent(WorldObject *parent);
    };
}
#endif
