#include <gtest/gtest.h>

#include "olympus.hpp"
#include "../olympus_test.hpp"
#include "render/texture.hpp"

#include "render_fixture.hpp"

using namespace olympus;

class TextureTest : public RenderTest {
protected:
    virtual void SetUp() {
        texture = new Texture(Texture::TEXTURE_2D);
    }
    
    virtual void TearDown() {
        delete texture;
    }
    Texture *texture;
};

TEST_F (TextureTest, LoadImage) {
    texture->load_image(OLYMPUS_ROOT_DIR "/test/render/assets/test-texture.jpg");
}

TEST_F (TextureTest, LoadBadImage) {
    logger_expect_error(true);
    
    try {
        texture->load_image("bad file name");
        EXPECT_TRUE(false);
    } catch (...) {
        //pass, we're good
    }
    
    logger_expect_error(false);
}

TEST_F(TextureTest, Load2DImageOn3DTexture) {
    delete texture;
    texture = new Texture(Texture::TEXTURE_3D);
    texture->load_image(OLYMPUS_ROOT_DIR "/test/render/assets/test-texture.jpg");
    EXPECT_TRUE(logger_contains_string("Attempted to load an 2D image into a texture that is not 2D"));
}