#ifndef OLYMPUS__RENDER__FRAMEBUFFER
#define OLYMPUS__RENDER__FRAMEBUFFER

#include "render/texture.hpp"

namespace olympus {
    class Framebuffer {
        Framebuffer();
        ~Framebuffer();
        
        Texture *get_color_texture();
        
        /**
         * Bind this framebuffer to the current render context.
         * All future writes will go into this buffer until it
         * another bound call is made.
         */
        void bind();
        
        /**
         * Attach a texture to this frame buffer, by default
         * this will attach the texture to color attachement 0.
         * More complicated attachement can use the paramaterized
         * versions of this function.
         */
        void attach_texture(Texture *texture);
        
        //TODO: Add more parameters
        //void attach_texture(

    };
}
#endif
