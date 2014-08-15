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
         * Using the default without assigning a slot will simply assign
         * the texture to slot 0.
         */
        bool add_texture(Texture *texture);
        
        /**
         * The parametrized version allows for more fine grained control
         * over where the texture goes.
         */
        bool add_texture(Texture *texture, unsigned slot);
        
        /**
         * This will try to remove a texture from the asset. Returns true
         * if the texture was found on the asset and false otherwise.
         */
        bool remove_texture(Texture *texture);
        
        /**
         * This will null out a slot. It return true if there was an item
         * in that slot
         */
        bool remove_texture(unsigned slot);
        
        Mesh *get_mesh();
        Renderer *get_renderer();
        Texture **get_textures();
    };
};
#endif
