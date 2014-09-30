#ifndef OLYMPUS__TERRAIN__WATER
#define OLYMPUS__TERRAIN__WATER

#include "world/renderable.hpp"

namespace olympus {
    class Water : public Renderable {
    private:
        unsigned _size;
        float _time;
        float _wave_height;
        float _wave_width;
        
        static Renderer *_get_renderer();
        Mesh *_generate_mesh();
        Texture *_generate_heightmap();
    public:
        Water(unsigned detail, float wave_height, float wave_width);
        ~Water();
        
        // TODO: This simulate function should probably belong to something higher up the chain.
        void simulate();
        
        void pre_render();
    };
}
#endif
