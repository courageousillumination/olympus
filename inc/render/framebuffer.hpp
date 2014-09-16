#ifndef OLYMPUS__RENDER__FRAMEBUFFER
#define OLYMPUS__RENDER__FRAMEBUFFER

#include "render/texture.hpp"

namespace olympus {
    class Framebuffer {
    private:
        unsigned _frame_buffer_id;
        Texture *_color_0_texture;
        Texture *_depth_texture;
        
    public:
        Framebuffer();
        ~Framebuffer();
        
        Texture *get_color_texture();
        Texture *get_depth_texture();
        
        // For internal use only.
        unsigned get_internal_id();

    };
}
#endif
