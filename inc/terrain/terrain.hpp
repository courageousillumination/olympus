#ifndef OLYMPUS__TERRAIN__TERRAIN
#define OLYMPUS__TERRAIN__TERRAIN

#include "world/renderable.hpp"

namespace olympus {
    class Terrain : public Renderable {
    public:
        Terrain();
        ~Terrain();
        
        /**
         * Generates a mesh with an optional seed.
         */
        static Mesh *generate_mesh();
        static Mesh *generate_mesh(unsigned seed);
    };
}
#endif
