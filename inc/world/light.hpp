#ifndef OLYMPUS__WORLD__LIGHT
#define OLYMPUS__WORLD__LIGHT

#include "world/world_object.hpp"
#include "world/viewpoint.hpp"

namespace olympus {
    /**
     * A light is a world object that will represent a simple lightsource.
     * In addition to the normal world_object methods, a light contains
     * a viewpoint, and specifics for setting the direction.
     */
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
        /// Each light has a viewpoint that is used for shadow rendering
        Viewpoint *_viewpoint;
        
        void _update_viewpoint();
    public:
        Light(LightType type);
        ~Light();
        
        /**
         * Overriden so that we can register ourselves with the root.
         */
        void set_parent(WorldObject *parent);
        
        void set_type(LightType type);
        LightType get_type();
        
        Viewpoint *get_viewpoint();
        
        //NOTE: The next five functions should be used only with DIRECTIONAL lights
        void set_direction(float x, float y, float z);
        void set_direction(glm::vec3 direction);
        /**
         * Set the box that completely defines the shadowed region (this internally just
         * calls to the viewpoint)
         */
        void set_shadow_box(glm::vec2 x, glm::vec2 y, glm::vec2 z);
       
        void get_direction(float &x, float &y, float &z);
        glm::vec3 get_direction();
    };
}
#endif
