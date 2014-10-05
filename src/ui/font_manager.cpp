#include <ft2build.h>
#include FT_FREETYPE_H

#include "debug/logger.hpp"

#include "ui/font_manager.hpp"

using namespace olympus;

// Should this be a class variable?
static FT_Library *_library;
   
FontManager::FontManager() {
    _library = new FT_Library;
    if (FT_Init_FreeType(_library)) {
        LOG(Logger::ERROR, "There was an error initializing FreeType\n");
    }
    LOG(Logger::DEBUG, "Initalized Freetype");
}

FontManager::~FontManager() {
    FT_Done_FreeType(*_library);
    delete _library;
}

FontManager &FontManager::get_instance() {
    static FontManager instance;
    return instance;
}

FontAtlas *FontManager::create_font_atlas(std::string font_file, unsigned px) {
    return new FontAtlas(font_file, px, _library);
}