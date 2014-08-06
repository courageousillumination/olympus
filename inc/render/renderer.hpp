#ifndef OLYMPUS__RENDER__RENDERER
#define OLYMPUS__RENDER__RENDERER

#include <string>

namespace olympus {
    /**
     * The renderer is the closest thing we have to 
     * a shader in olympus. Models can use this attached
     * to a material, or some internal proccesses can use these
     * "shaders" directly.
     */
    class Renderer {
    private:
        unsigned _shader_id;
        
        unsigned _compile_shader(const char *path, unsigned type);
        std::string _read_file(const char *path);
        unsigned _link(unsigned num_shaders, unsigned shaders[]);
        
    public:
        Renderer(const char *vertex_shader_path,
                 const char *fragment_shader_path);
        
        ~Renderer();
        
        void bind();
        
        //TODO: Add a renderer cache.
    };
};
#endif
