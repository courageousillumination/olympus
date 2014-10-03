#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/texture.hpp"

#include "common/olympus_environment.hpp"
#include "common/fixtures/window_fixture.hpp"

using namespace olympus;

class TextureTest : public WindowedTest {
protected:
    virtual void SetUp() {
        WindowedTest::SetUp();
        texture = new Texture(Texture::TEXTURE_2D);
    }
    
    virtual void TearDown() {
        delete texture;
        WindowedTest::TearDown();
    }

    Texture *texture;
};

TEST_F (TextureTest, LoadImage) {
    texture->load_image(OLYMPUS_ROOT_DIR "/test/assets/test-texture.jpg");
}

TEST_F (TextureTest, LoadBadImage) {
    get_test_appender()->set_expect_error(true);
    
    try {
        texture->load_image("bad file name");
        EXPECT_TRUE(false);
    } catch (...) {
        EXPECT_TRUE(get_test_appender()->contains_string("Failed to load image for texture bad file name"));
    }
    
    get_test_appender()->set_expect_error(false);
}

TEST_F(TextureTest, Load2DImageOn3DTexture) {
    delete texture;
    
    texture = new Texture(Texture::TEXTURE_3D);
    texture->load_image(OLYMPUS_ROOT_DIR "/test/assets/test-texture.jpg");
    EXPECT_TRUE(get_test_appender()->contains_string("Attempted to load an 2D image into a texture that is not 2D"));
}

TEST_F(TextureTest, SetParameters) {
    texture->set_parameter(Texture::Wrap, Texture::Repeat);
    
    EXPECT_EQ(Texture::Repeat, texture->get_parameter(Texture::Wrap));
    EXPECT_EQ(Texture::Repeat, texture->get_parameter(Texture::WrapS));
    EXPECT_EQ(Texture::Repeat, texture->get_parameter(Texture::WrapT));
    
    texture->set_parameter(Texture::WrapS, Texture::Clamp);
    
    EXPECT_EQ(Texture::Invalid, texture->get_parameter(Texture::Wrap));
    EXPECT_EQ(Texture::Clamp, texture->get_parameter(Texture::WrapS));
    EXPECT_EQ(Texture::Repeat, texture->get_parameter(Texture::WrapT));
    
    texture->set_parameter(Texture::WrapT, Texture::Clamp);
    
    EXPECT_EQ(Texture::Clamp, texture->get_parameter(Texture::Wrap));
    EXPECT_EQ(Texture::Clamp, texture->get_parameter(Texture::WrapS));
    EXPECT_EQ(Texture::Clamp, texture->get_parameter(Texture::WrapT));
}