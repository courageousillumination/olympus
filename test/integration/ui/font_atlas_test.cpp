#include <gtest/gtest.h>

#include "olympus.hpp"

#include "common/fixtures/window_fixture.hpp"

#define FONT "/usr/share/fonts/TTF/arial.ttf"
#define FONT_SIZE 12


using namespace olympus;

class FontAtlasIntegration : public WindowedTest {
protected:
    virtual void SetUp() {
        WindowedTest::SetUp();
        atlas = FontManager::get_instance().create_font_atlas(FONT, FONT_SIZE);
    }
    
    virtual void TearDown() {
        delete atlas;
        WindowedTest::TearDown();
    }
    
    FontAtlas *atlas;
};

TEST_F (FontAtlasIntegration, HasCorrectCoordinates) {
    // Make sure all the lower case letters have coordinates that look some
    // what correct.
    for (unsigned char i = 'a'; i < 'z'; i++) {
        CharacterInfo info = atlas->get_character_info(i);
        EXPECT_NE(0, info.width);
        EXPECT_NE(0, info.height);
    }
}

TEST_F (FontAtlasIntegration, HasTexture) {
    // I don't have a good way to test that the texture is correct right now,
    // but we need to test to make sure it's there
    EXPECT_TRUE(nullptr != atlas->get_texture());
}

TEST_F (FontAtlasIntegration, AllowsForDifferentSizes) {
    FontAtlas *bigger = FontManager::get_instance().create_font_atlas(FONT, FONT_SIZE * 2);
    for (unsigned char i = 'a'; i < 'z'; i++) {
        EXPECT_LT(atlas->get_character_info(i).width, bigger->get_character_info(i).width);
        EXPECT_LT(atlas->get_character_info(i).height, bigger->get_character_info(i).height);
    }
    delete bigger;
}