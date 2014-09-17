#include <fstream>

#include <GL/glew.h>

#include "debug/logger.hpp"

#include "render/renderer.hpp"

using namespace olympus;

std::string Renderer::_read_file(const char *path) {
    std::string line;
    std::string code;
    
    std::ifstream fin(path);
    if (!fin.good()) {
        LOG(Logger::ERROR, "Failed to open shader %s", path);
        return code;
    }
    while(fin.good()) {
        getline(fin, line);
        code += "\n" + line;
    }
    fin.close();
    return code;
}

unsigned Renderer::_compile_shader(const char *path, unsigned type) {
    std::string code = _read_file(path);
    LOG(Logger::DEBUG, "Starting compile of %s", path);
    
    unsigned shader_id = glCreateShader(type);
    
    const char *source = code.c_str();
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);
    
    //Check that compilation finished
    int result, info_log_length;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) {
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        char *errors = new char[info_log_length];
        glGetShaderInfoLog(shader_id, info_log_length, NULL, errors);
        LOG(Logger::ERROR, "Failed to compile shader %s. Error(s): %s", path, errors);
        delete []errors;
        return 0;
    }
    LOG(Logger::DEBUG, "Compiled %s", path);
    
    return shader_id;
}

unsigned Renderer::_link(unsigned num_shaders, unsigned shaders[]) {
    LOG(Logger::DEBUG, "Begin linking shader");
    unsigned program_id = glCreateProgram();
    for (unsigned i = 0; i < num_shaders; i++) {
        glAttachShader(program_id, shaders[i]);
    }
    glLinkProgram(program_id);
    
    //Check for link errors
    int result, info_log_length;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
        char *errors = new char[info_log_length];
        glGetProgramInfoLog(program_id, info_log_length, NULL, errors);
        LOG(Logger::ERROR, "Failed to link shader. Error(s): %s", errors);
        delete []errors;
        return 0;
    }
    
    LOG(Logger::DEBUG, "Linked shaders");
    return program_id;
    
}

Renderer::Renderer(const char *vertex_shader_path,
                   const char *fragment_shader_path) {
    unsigned shaders[2];
    shaders[0] = _compile_shader(vertex_shader_path, GL_VERTEX_SHADER);
    shaders[1] = _compile_shader(fragment_shader_path, GL_FRAGMENT_SHADER);
    _shader_id = _link(2, shaders);
    
    //Clean up
    glDeleteShader(shaders[0]);
    glDeleteShader(shaders[1]);
}

Renderer::~Renderer() {
    glDeleteProgram(_shader_id);
}

void Renderer::bind() {
    glUseProgram(_shader_id);
}

unsigned Renderer::get_internal_id() {
    return _shader_id;
}

bool Renderer::has_uniform(std::string id) {
    return (glGetUniformLocation(_shader_id, id.c_str()) != -1);
}

unsigned Renderer::get_uniform_location(std::string id) {
    int value = glGetUniformLocation(_shader_id, id.c_str());
    if (value == -1) {
        LOG(Logger::WARN, "Tried to fetch location of a non-existent uniform %s from a shader", id.c_str());
    }
    return (unsigned) value;
}

void Renderer::set_uniform(std::string id, glm::vec3 value) {
    glUniform3fv(get_uniform_location(id), 1, &value[0]);
}

void Renderer::set_uniform(std::string id, glm::vec2 value) {
    glUniform2fv(get_uniform_location(id), 1, &value[0]);
}

void Renderer::set_uniform(std::string id, glm::mat4 value) {
    glUniformMatrix4fv(get_uniform_location(id), 1, GL_FALSE, &value[0][0]);
}

void Renderer::set_uniform(std::string id, float value) {
    glUniform1f(get_uniform_location(id), value);
}

void Renderer::set_uniform(std::string id, int value) {
    glUniform1i(get_uniform_location(id), value);
}

void Renderer::set_uniform(std::string id, glm::mat4 *values, unsigned num_values) {
    glUniformMatrix4fv(get_uniform_location(id), num_values, GL_FALSE, &values[0][0][0]);
}

void Renderer::set_uniform(std::string id, glm::vec3 *values, unsigned num_values) {
    glUniform3fv(get_uniform_location(id), num_values, &values[0][0]);
}

void Renderer::set_uniform(std::string id, glm::vec2 *values, unsigned num_values) {
    glUniform2fv(get_uniform_location(id), num_values, &values[0][0]);
}

void Renderer::set_uniform(std::string id, int *values, unsigned num_values) {
    glUniform1iv(get_uniform_location(id), num_values, values);
}

void Renderer::set_uniform(std::string id, float *values, unsigned num_values) {
    glUniform1fv(get_uniform_location(id), num_values, values);
}