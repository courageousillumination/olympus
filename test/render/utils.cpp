#include <iostream>

#include <GL/glew.h>

#include "utils.hpp"

using namespace olympus;

bool expect_color_block(unsigned x, unsigned y,
                        unsigned width, unsigned height,
                        float r, float g, float b) {
    float *data = new float[width * height * 3];
    glReadPixels(x, y, width, height, GL_RGB, GL_FLOAT, data);
    bool valid = true;
    for (unsigned i = 0; i < width * height; i++) {
        if (data[i * 3] != r ||
            data[i * 3 + 1] != g ||
            data[i * 3 + 2] != b) {
            valid = false;
            break;
        }
    }
    delete []data;
    return valid;
}

Renderable *create_square(float x, float y, float width, float height,
                          float r, float g, float b) {
    Renderer *renderer = new Renderer(FLAT_VERTEX_SHADER,
                                        FLAT_FRAGMENT_SHADER);

    const float verts[] = {
        x, y, 0.0f,
        x + width, y, 0.0f,
        x, y + height, 0.0f,
        x + width, y + height, 0.0f
    };
    
    const float colors [] = {
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b
    };
    
    Mesh *mesh = new Mesh(2, Mesh::TRIANGLE_STRIP);
    mesh->set_vertex_attribute(0, 3, 4, verts);
    mesh->set_vertex_attribute(1, 3, 4, colors);

    //Create an asset to wrap all of the above
    Asset *asset = new Asset;
    asset->set_mesh(mesh);
    asset->set_renderer(renderer);
    
    Renderable *renderable = new Renderable;
    renderable->asset = asset;
    
    return renderable;
}

void destroy_square(Renderable *renderable) {
    delete renderable->asset->get_mesh();
    delete renderable->asset->get_renderer();
    delete renderable->asset;
    delete renderable;
}
