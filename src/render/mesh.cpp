#include <GL/glew.h>

#include "debug/logger.hpp"

#include "render/mesh.hpp"

using namespace olympus;

Mesh::Mesh(unsigned num_attributes, enum Mesh::PrimType prim_type) {
    glGenVertexArrays(1, &_vao_id);
    glBindVertexArray(_vao_id);
    _attributes = new unsigned[num_attributes];
    glGenBuffers(num_attributes, _attributes);
    _num_verts = 0;
    _indexed = false;
    switch (prim_type) {
        case TRIANGLES:
            _prim_type = GL_TRIANGLES;
            break;
        case TRIANGLE_FAN:
            _prim_type = GL_TRIANGLE_FAN;
            break;
        case TRIANGLE_STRIP:
            _prim_type = GL_TRIANGLE_STRIP;
            break;
    }
}

Mesh::~Mesh() {
    delete []_attributes;
}

void Mesh::set_vertex_attribute(unsigned attribute_number, unsigned dims,
                                unsigned num_vertices, const float *data) {
    if (_num_verts == 0) {
        _num_verts = num_vertices;
    } else if (_num_verts != num_vertices) {
        LOG(Logger::WARN, "Mesh got unexpected number of vertices: expected %d, got %d", _num_verts, num_vertices);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, _attributes[attribute_number]);
    glBufferData(GL_ARRAY_BUFFER, dims * num_vertices * sizeof(float), data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(attribute_number);
    glVertexAttribPointer(attribute_number, dims, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::set_indices(unsigned num_indices, const unsigned *indices) {
    if (indices == nullptr) {
        _indexed = false;
        return;
    }
    
    _indexed = true;
    _num_indices = num_indices;
    bind();
    
    glGenBuffers(1, &_element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(unsigned), indices, GL_STATIC_DRAW);
}

void Mesh::bind() {
    glBindVertexArray(_vao_id);
}

void Mesh::draw() {
    if (_indexed) {
        glDrawElements(_prim_type, _num_indices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(_prim_type, 0, _num_verts);
    }
}