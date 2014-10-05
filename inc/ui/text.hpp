#ifndef OLYMPUS__UI__TEXT
#define OLYMPUS__UI__TEXT

#include <string>

#include "world/renderable.hpp"
#include "ui/font_atlas.hpp"

namespace olympus {
    class Text : public Renderable {
    private:
        FontAtlas *_atlas;
        std::string _text;
        
        void _add_char(unsigned char c, float &base_x, float base_y,
                       glm::vec3 *vert, glm::vec2 *tex);
    public:
        Text(Renderer *renderer, FontAtlas *atlas);
        ~Text();
        
        /**
         * Set the text to a specified string. This will force the mesh to be regenerated,
         * using the current FontAtlas.
         */
        void set_text(std::string text);
        
        /**
         * Set the maximum width of a line of text. If we would hit this width we will do
         * line wrapping instead.
         */
        void set_text_width(unsigned pixels);
        
        std::string get_text();
        unsigned get_text_width();
    };
}
#endif
