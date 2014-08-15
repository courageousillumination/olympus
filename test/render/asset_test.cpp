#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/asset.hpp"

#include "render_fixture.hpp"

using namespace olympus;

class AssetTest : public RenderTest {
protected:
    virtual void SetUp() {
        asset = new Asset;
        renderable = new Renderable;
        renderable->asset = asset;
    }
    
    virtual void TearDown() {
        delete renderable;
        delete asset;
    }
    
    Asset *asset;
    Renderable *renderable;
};

TEST_F (AssetTest, AddTexture) {
    EXPECT_FALSE(asset->add_texture(nullptr, -1));
    EXPECT_FALSE(asset->add_texture(nullptr, MAX_ASSET_TEXTURES + 1));
    EXPECT_TRUE(asset->add_texture(nullptr));
    EXPECT_TRUE(asset->add_texture(nullptr, 0));
}


TEST_F (AssetTest, RemoveTexture) {
    Texture *texture1 = new Texture(Texture::TEXTURE_2D);
    Texture *texture2 = new Texture(Texture::TEXTURE_2D);
    
    asset->add_texture(texture1);
    
    EXPECT_FALSE(asset->remove_texture(2));
    EXPECT_FALSE(asset->remove_texture(texture2));
    EXPECT_TRUE(asset->remove_texture(texture1));
    
    asset->add_texture(texture1, 0);
    asset->add_texture(texture2, 1);
    
    EXPECT_TRUE(asset->remove_texture(texture1));
    EXPECT_TRUE(asset->remove_texture(texture2));
}
