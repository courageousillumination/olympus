#include <GL/glew.h>

#include "debug/logger.hpp"

#include "render/resource_manager.hpp"

using namespace olympus;


ResourceManager::ResourceManager() {
    _num_allocs = 0;
    _num_frees = 0;
}

ResourceManager::~ResourceManager() {
    
}

ResourceManager &ResourceManager::get_instance() {
    static ResourceManager manager;
    return manager;
}

unsigned ResourceManager::get_resource(ResourceType type) {
    unsigned result = 0;
    get_resources(type, 1, &result);
    return result;
}
        
void ResourceManager::get_resources(ResourceType type, unsigned num, unsigned values[]) {
    switch (type) {
        case ResourceManager::TEXTURE:
            glGenTextures(num, values);
            break;
        case ResourceManager::VERTEX_ARRAY:
            glGenVertexArrays(num, values);
            break;
        case ResourceManager::BUFFER:
            glGenBuffers(num, values);
            break;
        case ResourceManager::FRAMEBUFFER:
            glGenFramebuffers(num, values);
            break;
    }
    _num_allocs += num;
}

void ResourceManager::release_resource(ResourceType type, unsigned id) {
    release_resources(type, 1, &id);
}

void ResourceManager::release_resources(ResourceType type, unsigned num, unsigned values[]) {
    switch (type) {
        case ResourceManager::TEXTURE:
            glDeleteTextures(num, values);
            break;
        case ResourceManager::VERTEX_ARRAY:
            glDeleteVertexArrays(num, values);
            break;
        case ResourceManager::BUFFER:
            glDeleteBuffers(num, values);
            break;
        case ResourceManager::FRAMEBUFFER:
            glDeleteFramebuffers(num, values);
            break;
    }
    _num_frees += num;
}

void ResourceManager::check_allocation() {
    if (_num_allocs != _num_frees) {
        LOG(Logger::ERROR, "Detected graphics resource leak (%d allocs, %d frees)", _num_allocs, _num_frees);
    }
    else {
        LOG(Logger::DEBUG, "No memory leaks detected.");
    }
}
