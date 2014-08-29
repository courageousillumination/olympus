#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/asset.hpp"

#include "common/olympus_environment.hpp"

using namespace olympus;

class AssetTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        asset = new Asset;
    }
    
    virtual void TearDown() {
        delete asset;
    }
    
    Asset *asset;
};

TEST_F (AssetTest, AddTexture) {
    EXPECT_FALSE(asset->add_texture(nullptr, -1));
    EXPECT_FALSE(asset->add_texture(nullptr, MAX_ASSET_TEXTURES));
    EXPECT_TRUE(asset->add_texture(nullptr));
    for (int i = 0; i < MAX_ASSET_TEXTURES; i++) {
        EXPECT_TRUE(asset->add_texture(nullptr, i));
    }
}


TEST_F (AssetTest, RemoveTexture) {
    Texture *texture1 = new Texture();
    Texture *texture2 = new Texture();
    
    asset->add_texture(texture1);
    
    EXPECT_FALSE(asset->remove_texture(2));
    EXPECT_FALSE(asset->remove_texture(texture2));
    EXPECT_TRUE(asset->remove_texture(texture1));
    
    asset->add_texture(texture1, 0);
    asset->add_texture(texture2, 1);
    
    EXPECT_TRUE(asset->remove_texture(texture1));
    EXPECT_TRUE(asset->remove_texture(1));
    
    asset->add_texture(texture1);
    asset->add_texture(texture2);
    EXPECT_TRUE(get_test_appender()->contains_string("Attempting to add a texture to texture slot 0 which already has a texture in it"));
    
    delete texture1;
    delete texture2;
}
