#ifndef OLYMPUS__UI__FONT_MANAGER
#define OLYMPUS__UI__FONT_MANAGER

#include "ui/font_atlas.hpp"

namespace olympus {
    /**
     * Class for controlling Fonts. All atlases should be created through
     * this class (they can be deleted normally). This is to ensure that freetype
     * can be initalized before anything else
     */
    class FontManager {
    private:
        FontManager();
        
        FontManager(FontManager const&);
        void operator=(FontManager const&);
    public:
        ~FontManager();
        
        static FontManager &get_instance();
        
        FontAtlas *create_font_atlas(std::string font_file, unsigned px);
    };
};
#endif
