#ifndef OLYMPUS__RENDER__WORLD
#define OLYMPUS__RENDER__WORLD

#include "render/render_engine.hpp"
#include "render/world_object.hpp"
#include "render/light.hpp"
#include "render/renderable.hpp"

namespace olympus {
    class World : public WorldObject {
    private:
        RenderEngine *_render_engine;
        
        std::set<Renderable *> _renderables;
        std::set<Light *> _lights;
    public:
        World();
        
        void set_render_engine(RenderEngine *render_engine);
        RenderEngine *get_render_engine();
        
        void add_renderable(Renderable *r);
        void add_light(Light *l);
        void remove_renderable(Renderable *r);
        void remove_light(Light *l);
        
        std::set<Renderable *> get_renderables();
        std::set<Light *> get_lights();
        
    };
}
#endif
