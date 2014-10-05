#ifndef OLYMPUS__UI__FONT_ATLAS
#define OLYMPUS__UI__FONT_ATLAS

#include <string>

#include <glm/glm.hpp>

#include "render/texture.hpp"

namespace olympus {
    /**
     * This struct contains all the information about a given character.
     * This includes its dimensions, and its position in the texture.
     */
    struct CharacterInfo {
        short width, height; // In pixels, for creating a mesh
        short top, left, advance;
        // Texture coordinates of this character (may not be vertically upright)
        float x1, x2, y1, y2;
    };
    
    class FontAtlas {
    private:
        CharacterInfo _character_info[128];
        Texture *_atlas;
    public:
        FontAtlas(std::string font_file, unsigned px, void *library);
        ~FontAtlas();
        
        CharacterInfo get_character_info(unsigned char val);
        Texture *get_texture();
    };
}
#endif
