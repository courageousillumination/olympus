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
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        char *errors = new char[info_log_length];
        glGetShaderInfoLog(shader_id, info_log_length, NULL, errors);
        LOG(Logger::ERROR, "Failed to compile shader. Error(s): %s", errors);
        delete errors;
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
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        char *errors = new char[info_log_length];
        glGetProgramInfoLog(program_id, info_log_length, NULL, errors);
        LOG(Logger::ERROR, "Failed to link shader. Error(s): %s", errors);
        delete errors;
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