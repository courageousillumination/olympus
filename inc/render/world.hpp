#ifndef OLYMPUS__RENDER__WORLD
#define OLYMPUS__RENDER__WORLD

#include <vector>

#include "render/world_object.hpp"
#include "render/light.hpp"
#include "render/renderable.hpp"

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
