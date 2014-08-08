#ifndef OLYMPUS__RENDER__ASSET
#define OLYMPUS__RENDER__ASSET

#include "render/mesh.hpp"
#include "render/renderer.hpp"
#include "render/texture.hpp"

#define MAX_ASSET_TEXTURES 9

namespace olympus {
    /**
     * An asset is simply a wrapper for meshs/renderers(materials?) and
     * textures.
     */
    class Asset {
    private:
        Mesh *_mesh;
        Renderer *_renderer;
        Texture *_textures[MAX_ASSET_TEXTURES];
    public:
        Asset();
        
        void set_mesh(Mesh *mesh);
        void set_renderer(Renderer *renderer);
        /**
         * By default this will add it to the end of the texture list
         */
        void add_texture(Texture *texture);
        void add_texture(Texture *texture, unsigned slot);
        
        void remove_texture(Texture *texture);
        void remove_texture(unsigned slot);
        
        Mesh *get_mesh();
        Renderer *get_renderer();
        Texture **get_textures();
    };
};
#endif
