#include "debug/logger.hpp"
#include "render/asset.hpp"

using namespace olympus;

Asset::Asset() {
    for (unsigned i = 0; i < MAX_ASSET_TEXTURES; i++) {
        _textures[i] = nullptr;
    }
}

void Asset::set_mesh(Mesh *mesh) {
    _mesh = mesh;
}

void Asset::set_renderer(Renderer *renderer) {
    _renderer = renderer;
}

bool Asset::add_texture(Texture *texture) {
    return add_texture(texture, 0);
}

bool Asset::add_texture(Texture *texture, unsigned slot) {
    if (slot < MAX_ASSET_TEXTURES) {
        if (_textures[slot] != nullptr) {
            LOG(Logger::WARN, "Attempting to add a texture to texture slot %d which already has a texture in it", slot);
        }
        _textures[slot] = texture;
        return true;
    } else {
        return false;
    }
}

bool Asset::remove_texture(Texture *texture) {
    for (unsigned i = 0; i < MAX_ASSET_TEXTURES; i++) {
        if (_textures[i] == texture) {
            _textures[i] = nullptr;
            return true;
        }
    }
    return false;
}

bool Asset::remove_texture(unsigned slot) {
    if (_textures[slot] != nullptr) {
        _textures[slot] = nullptr;
        return true;
    }
    return false;
}

Mesh *Asset::get_mesh() {
    return _mesh;
}

Renderer *Asset::get_renderer() {
    return _renderer;
}

Texture **Asset::get_textures() {
    return _textures;
}