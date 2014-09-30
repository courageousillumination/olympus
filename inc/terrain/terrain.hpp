#ifndef OLYMPUS__TERRAIN__TERRAIN
#define OLYMPUS__TERRAIN__TERRAIN

#include "world/renderable.hpp"

namespace olympus {
    /**
     * A Terrain can be used to represent a natural landscape like mountains.
     * Each one is a renderable and controls its own asset. Although it will
     * create a mesh, it requries that you pass in a renderer for the asset;
     * it will not own the renderer.
     */
    
    class Terrain : public Renderable {
    private:
        unsigned _seed;
        unsigned _size;
        
        // These two can be used to fine tune the diamond square algorithm
        float _max_displacement;
        float _falloff;
        
        float *_height_map;
        
        /**
         * If the height map has not yet been created this will
         * create the height map. Otherwise this will just return.
         */
        float *_generate_height_map();
        
        void _generate_height_map_helper(float *values, unsigned x1, unsigned y1, 
                                         unsigned x2, unsigned y2, unsigned level, float max_displacement);
        
        /**
         * Creates a mesh that represents this terrain.
         */
        Mesh *_generate_mesh();
    public:
        /**
         * Creates a terrain with the default values and a given renderer.
         */
        Terrain(Renderer *renderer);
        
        /**
         * Parameterzied constructor. Detail specifies how many verticies will be added
         * to the terrain (2 ^ detail).
         */
        Terrain(Renderer *renderer,
                unsigned seed, unsigned detail, float max_displacement, float falloff);
        
        ~Terrain();  
        
        float *get_height_map();
    };
}
#endif
