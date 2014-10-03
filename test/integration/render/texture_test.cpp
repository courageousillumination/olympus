#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/texture.hpp"

#include "common/test_block.hpp"
#include "common/olympus_environment.hpp"
#include "common/fixtures/world_fixture.hpp"

using namespace olympus;

static glm::vec3 points[] = {
    glm::vec3(-1.0, -1.0, 0),
    glm::vec3(1.0, -1.0, 0),
    glm::vec3(-1.0, 1.0, 0),
    
    glm::vec3(-1.0, 1.0, 0),
    glm::vec3(1.0, -1.0, 0),
    glm::vec3(1.0, 1.0, 0)
};

static glm::vec2 texture_coords[] = {
    glm::vec2(0, 0),
    glm::vec2(1, 0),
    glm::vec2(0, 1),
    
    glm::vec2(0, 1),
    glm::vec2(1, 0),
    glm::vec2(1, 1)
};

class TextureTest : public WorldedTest {
protected:
    virtual void SetUp() {
        WorldedTest::SetUp();
        texture = new Texture(Texture::TEXTURE_2D);
        
        // Created a textured square
        mesh = new Mesh(2, Mesh::TRIANGLES);
        mesh->set_vertex_attribute(0, 3, 6, (float *)points);
        mesh->set_vertex_attribute(1, 2, 6, (float *)texture_coords);
        
        renderer = new Renderer(TEXTURE_VERTEX_SHADER,
                                TEXTURE_FRAGMENT_SHADER);
        
        asset = new Asset();
        asset->set_mesh(mesh);
        asset->set_renderer(renderer);
        asset->add_texture(texture);
        
        renderable = new Renderable;
        renderable->asset = asset;
        
        world->add_child(renderable);
    }
    
    virtual void TearDown() {
        delete mesh;
        delete renderer;
        delete asset;
        world->remove_child(renderable);
        delete renderable;
        delete texture;
        WorldedTest::TearDown();
    }

    Texture *texture;
    
    // Objects to attach the texture onto
    Renderable *renderable;
    Mesh *mesh;
    Renderer *renderer;
    Asset *asset;
};

TEST_F (TextureTest, LoadImage) {
    texture->load_image(OLYMPUS_ROOT_DIR "/test/assets/red-texture.png");
    window->render();
    
    // This is just a red image so we should expect to see a red screen
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1.0, 0.0, 0.0));
}

TEST_F (TextureTest, LoadData) {
    float *data = new float[64 * 64];
    
    for (unsigned i = 0; i < 64 * 64; i++) {
        data[i] = 0.5f;
    }
    
    texture->load_data(1, 64, 64, data);
    window->render();
    
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.5, 0.0, 0.0));
    
    delete []data;
    
    // Now try with multiple channels
    data = new float[64 * 64 * 3];
    
    for (unsigned i = 0; i < 64 * 64 * 3; i++) {
        data[i] = 0.5f;
    }
    
    texture->load_data(3, 64, 64, data);
    window->render();
    
    EXPECT_TRUE(expect_color_block(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.5, 0.5, 0.5));
    
    // Check that we get a warning
    get_test_appender()->set_expect_warning(true);
    texture->load_data(2, 64, 64, data);
    EXPECT_TRUE(get_test_appender()->contains_string("Tried to load data into a texture with an unspported number of channels 2"));
    get_test_appender()->set_expect_warning(false);
    
    delete []data;
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
    
    //Test some edge cases
    texture->set_parameter(Texture::Wrap, Texture::Invalid);
}