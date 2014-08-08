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
void Asset::add_texture(Texture *texture) {
    _textures[0] = texture; //TODO: Fix this!
}
void Asset::add_texture(Texture *texture, unsigned slot) {
    _textures[slot] = texture; //TODO: Bounds checking.
}

void Asset::remove_texture(Texture *texture) {
    //TODO
}
void Asset::remove_texture(unsigned slot) {
    _textures[slot] = nullptr;
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