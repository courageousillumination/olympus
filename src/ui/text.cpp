#include "ui/text.hpp"

using namespace olympus;

void Text::_add_char(unsigned char c, float &base_x, float base_y,
                     glm::vec3 *vert, glm::vec2 *tex) {
    CharacterInfo c_pos = _atlas->get_character_info(c);
    
    //TODO: Use GLFW to get the actual screen size
    float px = 2.0f / 640;
    float py = 2.0f / 480;

    float x, y, w, h;
    x = base_x * px + c_pos.left * px;
    y = base_y * py + c_pos.top * py;
    
    w = c_pos.width * px;
    h = -c_pos.height * py;
    
    //std::cout << x << " " << y << '\n';
    
    *vert++ = glm::vec3(x, y, 0.0);
    *vert++ = glm::vec3(x + w, y, 0.0);
    *vert++ = glm::vec3(x, y + h, 0.0);
    
    *vert++ = glm::vec3(x + w, y, 0.0);
    *vert++ = glm::vec3(x, y + h, 0.0);
    *vert++ = glm::vec3(x + w, y + h, 0.0);
    
    *tex++ = glm::vec2(c_pos.x1, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x2, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x1, c_pos.y2);
    
    *tex++ = glm::vec2(c_pos.x2, c_pos.y1);
    *tex++ = glm::vec2(c_pos.x1, c_pos.y2);
    *tex++ = glm::vec2(c_pos.x2, c_pos.y2);
    
    base_x += (c_pos.advance >> 6);
}

Text::Text(Renderer *renderer, FontAtlas *atlas) {
    asset = new Asset;
    asset->set_renderer(renderer);
    asset->set_mesh(nullptr); //We must fill out the mesh later
    asset->add_texture(atlas->get_texture());
    
    _atlas = atlas;
}

Text::~Text() {
    if (asset->get_mesh() != nullptr) {
        delete asset->get_mesh();
    }
    delete asset;
}

void Text::set_text(std::string text) {
    // Free up the old mesh if it's there
    if (asset->get_mesh() != nullptr) {
        delete asset->get_mesh();
    }
    
    _text = text;
    
    // Rebuild the mesh
    glm::vec3 verts[text.size() * 6];
    glm::vec2 texture_coords[text.size() * 6];
    glm::vec3 *v = verts;
    glm::vec2 *t = texture_coords;
    
    float base_x = 0;
    float base_y = 0;
    for (unsigned i = 0; i < text.size(); i++) {
        _add_char(text[i], base_x, base_y, v, t);
        v += 6;
        t += 6;
    }
    
    Mesh *mesh = new Mesh(2, Mesh::TRIANGLES);
    mesh->set_vertex_attribute(0, 3, text.size() * 6, (float *)verts);
    mesh->set_vertex_attribute(1, 2, text.size() * 6, (float *)texture_coords);
    
    asset->set_mesh(mesh);
}

void Text::set_text_width(unsigned pixels) {
    
}

std::string Text::get_text() {
    return _text;
}

unsigned Text::get_text_width() {
    return 0;
}