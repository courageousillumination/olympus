#ifndef OLYMPUS__WORLD__WORLD
#define OLYMPUS__WORLD__WORLD

#include <vector>

#include "fx/skybox.hpp"

#include "world/world_object.hpp"
#include "world/light.hpp"
#include "world/renderable.hpp"

namespace olympus {
    /**
     * A World is a specific type of WorldObject that should
     * be the root of any scene. It includes lists of all renderable
     * children, all light children, etc. so that the render_engine
     * has a single access point to these instead of having to walk
     * the tree.
     */
    class World : public WorldObject {
    private:
        std::set<Renderable *> _renderables;
        std::vector<Light *> _lights;
        Skybox *_skybox;
    public:
        World();
        
        void add_renderable(Renderable *r);
        void add_light(Light *l);
        void remove_renderable(Renderable *r);
        void remove_light(Light *l);
        
        const std::set<Renderable *> get_renderables();
        const std::vector<Light *> get_lights();
        
        void set_skybox(Skybox *skybox);
        Skybox *get_skybox();
    };
}
#endif
