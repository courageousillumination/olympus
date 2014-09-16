#ifndef OLYMPUS__RENDER__FRAMEBUFFER
#define OLYMPUS__RENDER__FRAMEBUFFER

#include "render/texture.hpp"

namespace olympus {
    class Framebuffer {
    private:
        unsigned _width, _height;
        unsigned _frame_buffer_id;
        
        int _max_color_attachments;
        Texture **_color_textures;
        Texture *_depth_texture;
    public:
        /**
         * Set up a framebuffer object. Width and height are used
         * to determine the resolution of the framebuffer, and all
         * textures attached to this framebuffer will inherit that 
         * resolution.
         */
        Framebuffer(unsigned width, unsigned height);
        ~Framebuffer();
        
        /**
         * This function will attach a texture to a framebuffer in
         * the given slot. NOTE: This will bind the framebuffer so
         * this shouldn't be called during a render call because
         * it could leave the graphics manager confused.
         */
        void attach_color_texture(Texture *texture, unsigned slot);
        void attach_depth_texture(Texture *texture);
        
        Texture *get_color_texture(unsigned slot);
        Texture *get_depth_texture();
        
        // For internal use only.
        unsigned get_internal_id();

    };
}
#endif
