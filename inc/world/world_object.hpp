#ifndef OLYMPUS__WORLD__WORLD_OBJECT
#define OLYMPUS__WORLD__WORLD_OBJECT

#include <set>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace olympus {
    
    class World;
    
    /**
     * This class represents anything that exists spatially in the
     * world. The only thing that this class provides is basic position
     * and inheritance from parents.
     * TODO: At some point this will probably have to play nicely with 
     * some physics engine. 
     */
    class WorldObject {
    protected:
        glm::vec3 _position, _scale;
        glm::quat _orientation;
        glm::mat4 _model_matrix;
        
        WorldObject *_parent;
        World *_root;
        std::set<WorldObject *> _children;

        /**
         * Whenever we change the position, scale, or orientation we need to
         * also update the model matrix.
         */
        void _update_model_matrix();
        
        /**
         * This function can be overriden by children to properly account
         * for post move operations.
         */
        virtual void _post_update_model_matrix() { }
        
        /**
         * This has been made private, so that we only expose the add_child function.
         */
        virtual void set_parent(WorldObject *parent);
    public:
        WorldObject();
        virtual ~WorldObject() {}
        
        /// NOTE: For positon/scale we provide the ability to use both glm
        ///  primatives and raw floats but we require quats for orientation.
        void set_position(glm::vec3 position);
        void set_position(float x, float y, float z);
        void set_scale(glm::vec3 scale);
        void set_scale(float x, float y, float z);
        void set_orientation(glm::quat orientation);
        void add_child(WorldObject *child);
        void remove_child(WorldObject *child);
        
        glm::vec3 get_position();
        void get_position(float &x, float &y, float &z);
        glm::vec3 get_scale();
        void get_scale(float &x, float &y, float &z);
        glm::quat get_orientation();
        WorldObject *get_parent();
        const std::set<WorldObject *> get_children();
        
        /**
         * Each object should have a singular root World
         */
        World *get_root();
        
        /**
         * The model matrix can't be set explicitly and is created
         * from the other parameters. NOTE: This model matrix will
         * be in world space, **not** parent space; it already takes
         * into account the parent position.
         */
        glm::mat4 get_model_matrix();
        
    };
}
#endif
