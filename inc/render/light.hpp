#ifndef OLYMPUS__RENDER__LIGHT
#define OLYMPUS__RENDER__LIGHT

#include "render/world_object.hpp"

namespace olympus {
    class Light : public WorldObject {
    public:
        enum LightType {
            DIRECTIONAL
        };
    private:
        LightType _type;
        /// In theory this could be encoded in the orientation, but this
        /// is much easier.
        glm::vec3 _direction;
    public:
        Light(LightType);
        
        /**
         * Overriden so that we can register ourselves with
         * the render engine.
         */
        void set_parent(WorldObject *parent);
        
        /**
         * Set the direction on a directional light
         */
        void set_direction(float x, float y, float z);
        void set_direction(glm::vec3 direction);
        
        void get_direction(float &x, float &y, float &z);
        glm::vec3 get_direction();
        
        void set_type(LightType type);
        LightType get_type();
        
    };
}
#endif
