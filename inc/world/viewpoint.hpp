#ifndef OLYMPUS__WORLD__VIEWPOINT
#define OLYMPUS__WORLD__VIEWPOINT

#include "world/world_object.hpp"

namespace olympus {
    /**
     * A viewpoint is a WorldObject with the additional functionality
     * of having a view matrix. This can either use perspective or ortho
     * perspective.
     */
    class Viewpoint : public WorldObject {
    private:
        glm::mat4 _projection_matrix;
        glm::mat4 _view_matrix;
        float _fov, _ratio, _near, _far;
        glm::vec2 _ortho_x, _ortho_y, _ortho_z;
        bool _use_ortho;
        
        void _update_projection_matrix();
        
        /** 
         * We need to override this method in order to update our view matrix as well
         * as the model matrix.
         */
        void _post_update_model_matrix();
    public:
        Viewpoint();
        virtual ~Viewpoint() { }
        
        void set_fov(float fov);
        void set_ratio(float ratio);
        void set_near(float near);
        void set_far(float far);
        void set_perspective(float fov, float ratio, float near, float far);
        /**
         * Right now this is the only way to set an orthographic projection.
         */
        void set_ortho(glm::vec2 x, glm::vec2 y, glm::vec2 z);
        
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
