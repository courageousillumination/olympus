#ifndef OLYMPUS__FX__SKYBOX
#define OLYMPUS__FX__SKYBOX

#include <string>

#include "render/texture.hpp"
#include "world/renderable.hpp"

namespace olympus {
    class Skybox : public Renderable {
    public:
        /**
         * Create a skybox with six images.
         */
        Skybox(const char *front,
               const char *back,
               const char *left,
               const char *right,
               const char *top,
               const char *bottom);
        ~Skybox();
        
        /**
         * Render the skybox. This will perform all
         * associated state changes, etc.
         */
        void render();
        
    };
}
#endif
