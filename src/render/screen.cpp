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


static GLuint vertexbuffer = 0;
 

void Screen::render() {
    if (vao_id == 0) {
        Renderer *renderer = new Renderer(FLAT_VERTEX_SHADER,
                                          FLAT_FRAGMENT_SHADER);
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
    }
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
};