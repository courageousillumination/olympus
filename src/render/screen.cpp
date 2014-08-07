#include <GL/glew.h>
#include <GL/gl.h>

#include "render/screen.hpp"
#include "render/renderer.hpp"
#include "render/shaders.hpp"

using namespace olympus;

static GLuint vao_id = 0;

static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

GLfloat cube_texcoords[] = {
    // front
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0
  };


static GLuint vertexbuffer = 0, vbo_cube_texcoords = 0;
 
static Texture *texture = nullptr;
static Renderer *renderer = nullptr;

Screen::Screen() {
    if (vao_id == 0) {
        glActiveTexture(GL_TEXTURE0);
        texture = new Texture(Texture::TEXTURE_2D);
        texture->load_image("/home/tristan/Development/olympus/texture.jpg");
        texture->bind();
        renderer = new Renderer(TEXTURE_VERTEX_SHADER,
                                          TEXTURE_FRAGMENT_SHADER);
        renderer->bind();
        
        
        glGenVertexArrays(1, &vao_id);
        glBindVertexArray(vao_id);
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );
        
        glGenBuffers(1, &vbo_cube_texcoords);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);
        /* onDisplay */
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
        glVertexAttribPointer(
            1, // attribute
            2,                  // number of elements per vertex, here (x,y)
            GL_FLOAT,           // the type of each element
            GL_FALSE,           // take our values as-is
            0,                  // no extra data between each position
            0                   // offset of first element
        );
    }
    
    _framebuffer = new Framebuffer;
}

void Screen::render() {
    _framebuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT);
    renderer->bind();
    texture->bind();
    glBindVertexArray(vao_id);
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    _framebuffer->unbind();
    
    //_framebuffer->get_color_texture()->bind();
    //glDrawArrays(GL_TRIANGLES, 0, 3);
};

Framebuffer *Screen::get_framebuffer() {
    return _framebuffer;
}