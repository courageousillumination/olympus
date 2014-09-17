#ifndef OLYMPUS__TERRAIN__WATER
#define OLYMPUS__TERRAIN__WATER

#include "world/renderable.hpp"

namespace olympus {
    class Water : public Renderable {
    private:
        
        static Renderer *_get_renderer();
        static Mesh *_generate_mesh();
        static Texture *_generate_heightmap(unsigned width, unsigned height);
    public:
        Water();
        ~Water();
        
        /**
         * Create the renderer, textures, etc that are needed for
         * water.
         */
        void generate();
        
        void destroy();
        
        void pre_render();
    };
}
#endif
