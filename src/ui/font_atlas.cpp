#include <algorithm>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "debug/logger.hpp"

#include "ui/font_atlas.hpp"

using namespace olympus;

static FT_Face load_face(FT_Library *library, std::string &font_file, unsigned px) {
    FT_Face face;
    char error = FT_New_Face(*library, font_file.c_str(), 0, &face);
    if (error == FT_Err_Unknown_File_Format) {
        LOG(Logger::ERROR, "Tried to open a font with an unknown font format.");
    }
    else if (error) {
        LOG(Logger::ERROR, "Could not find font file %s.", font_file.c_str());
    }

    FT_Set_Pixel_Sizes(face, 0, px);
    return face;
}

static unsigned find_bitmap_size(FT_Face face, int &row_height) {
    FT_GlyphSlot g = face->glyph;
    unsigned w = 0, h = 0;

    // We only care about characters from 32 to 128.
    for(unsigned char i = 32; i < 128; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            LOG(Logger::WARN, "Failde to load character %c", i);
            continue;
        }
        w += g->bitmap.width;
        h = std::max(h, g->bitmap.rows);
    }

    // Find nearest power of two bitmap size.
    // TOOD: Optimize this.
    float side_length = sqrt(w * h);
    unsigned bitmap_size = 1;
    while(bitmap_size < side_length) {
        bitmap_size <<= 1;
    }
    row_height = h;
    return bitmap_size;
}


FontAtlas::FontAtlas(std::string font_file, unsigned px, void *library) {
    memset(_character_info, 0, 128 * sizeof(CharacterInfo));

    //Attempt to load up the font file
    int row_height;
    FT_Face face = load_face((FT_Library*)library, font_file, px);
    FT_GlyphSlot g = face->glyph;
    unsigned bitmap_size = find_bitmap_size(face, row_height);

    // Now we can just fill out bitmap
    unsigned char *bitmap = new unsigned char[bitmap_size * bitmap_size];
    memset(bitmap, 0, bitmap_size * bitmap_size);

    unsigned x = 0, y = 0;
    for(unsigned i = 32; i < 128; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) continue;
        // Roll over as necessary
        if(x + g->bitmap.width >= bitmap_size) {
            y+= row_height;
            x = 0;
        }
        //Copy into our bitmap
        unsigned char *buff = g->bitmap.buffer;
        for (unsigned int j = 0; j < g->bitmap.rows; j++) {
            for (unsigned int k = 0; k < g->bitmap.width; k++) {
                bitmap[((y + j)) * bitmap_size + (x + k)] = *buff++;
            }
        }

        _character_info[i].width =  g->bitmap.width;
        _character_info[i].height = g->bitmap.rows;
        _character_info[i].top = g->bitmap_top;
        _character_info[i].left = g->bitmap_left;
        _character_info[i].advance = g->advance.x;

        // Add the texture coordinates
        _character_info[i].x1 = (float) x / bitmap_size;
        _character_info[i].y1 = (float) y / bitmap_size;
        _character_info[i].x2 = (float) (x + g->bitmap.width) / bitmap_size;
        _character_info[i].y2 = (float) (y + g->bitmap.rows) / bitmap_size;

        x += g->bitmap.width;
    }

    //Create the texture
    _atlas = new Texture(Texture::TEXTURE_2D);
    _atlas->load_data(1, bitmap_size, bitmap_size, bitmap);
    _atlas->set_parameter(Texture::Wrap, Texture::Clamp);

    delete []bitmap;

}

FontAtlas::~FontAtlas() {
    delete _atlas;
}

CharacterInfo FontAtlas::get_character_info(unsigned char val) {
    return _character_info[val];
}

Texture *FontAtlas::get_texture() {
    return _atlas;
}
