#ifndef OLYMPUS__RENDER__VIEWPOINT
#define OLYMPUS__RENDER__VIEWPOINT

#include "render/world_object.hpp"

namespace olympus {
    class Viewpoint : public WorldObject {
    private:
        glm::mat4 _projection_matrix;
        float _fov, _ratio, _near, _far;
        
        void _update_projection_matrix();
    public:
        virtual ~Viewpoint() { }
        
        void set_fov(float fov);
        void set_ratio(float ratio);
        void set_near(float near);
        void set_far(float far);
        void set_perspective(float fov, float ratio, float near, float far);
        
        float get_fov();
        float get_ratio();
        float get_near();
        float get_far();
        
        glm::mat4 get_view_matrix();
        glm::mat4 get_projection_matrix();
        glm::mat4 get_view_projection_matrix();
    };
}
#endif
