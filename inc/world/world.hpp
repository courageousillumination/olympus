#ifndef OLYMPUS__WORLD__WORLD
#define OLYMPUS__WORLD__WORLD

#include <vector>

#include "world/world_object.hpp"
#include "world/light.hpp"
#include "world/renderable.hpp"

namespace olympus {
    class World : public WorldObject {
    private:
        std::set<Renderable *> _renderables;
        std::vector<Light *> _lights;
    public:
        World();
        
        void add_renderable(Renderable *r);
        void add_light(Light *l);
        void remove_renderable(Renderable *r);
        void remove_light(Light *l);
        
        std::set<Renderable *> get_renderables();
        std::vector<Light *> get_lights();
        
    };
}
#endif
