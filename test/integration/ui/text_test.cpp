#include <gtest/gtest.h>

#include "olympus.hpp"

#include "common/square.hpp"
#include "common/test_block.hpp"
#include "common/olympus_environment.hpp"
#include "common/fixtures/world_fixture.hpp"

#define FONT "/usr/share/fonts/TTF/arial.ttf"

using namespace olympus;

class TextIntegration : public WorldedTest {
protected:
    virtual void SetUp() {
        WorldedTest::SetUp();
        text_renderer = new Renderer(TEXT_VERTEX_SHADER,
                                     TEXT_FRAGMENT_SHADER);
        font_atlas = FontManager::get_instance().create_font_atlas(FONT, 12);
        text = new Text(text_renderer, font_atlas);
        
        world->add_child(text);
    }
    
    virtual void TearDown() {
        world->remove_child(text);
        
        delete text;
        delete font_atlas;
        delete text_renderer;
        
        WorldedTest::TearDown();
    }
    
    Renderer *text_renderer;
    FontAtlas *font_atlas;
    Text *text;
};

TEST_F (TextIntegration, HasCorrectMesh) {
    text->set_text("Hello");
    EXPECT_EQ(30, text->asset->get_mesh()->get_num_verts()); // 6 per letter * 5 letters
}

TEST_F (TextIntegration, DISABLED_WrapsProperly) { //Pending wrapping
    text->set_text_width(50);
    text->set_text(std::string("a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a a")); // We expect a couple line wraps
    text->set_position(0, 0.9, 0);
    window->render();
    
    EXPECT_FALSE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT / 2, 0.0, 0.0, 0.0)); // Make sure there's something in the lower half of the screen
    
}