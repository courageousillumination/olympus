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
     * world. These need not be renderable, but must have a position.
     * It uses GLM internally to do most of the calculations
     * TODO: At some point this will probably have to play nicely with 
     * some physics engine. 
     */
    class WorldObject {
    protected:
        glm::vec3 _position, _scale;
        glm::quat _orientation;
        glm::mat4 _model_matrix;
        
        WorldObject *_parent;
        std::set<WorldObject *> _children;
        World *_root;
        
        void _update_model_matrix();
        /**
         * This function can be overriden by children to properly account
         * for post move operations.
         */
        virtual void _post_update_model_matrix() { }
        
        /**
         * This has been made private to simplify the upper levels.
         */
        virtual void set_parent(WorldObject *parent);
    public:
        WorldObject();
        virtual ~WorldObject() {}
        
        ///NOTE: All setters are declared virtual to allow
        ///subclasses to insert their own callbacks.
        ///NOTE: For getters and setters we provide the ability
        /// to use both glm primatives and raw floats
        virtual void set_position(glm::vec3 position);
        virtual void set_position(float x, float y, float z);
        virtual void set_scale(glm::vec3 scale);
        virtual void set_scale(float x, float y, float z);
        virtual void set_orientation(glm::quat orientation);
        virtual void add_child(WorldObject *child);
        virtual void remove_child(WorldObject *child);
        
        glm::vec3 get_position();
        void get_position(float &x, float &y, float &z);
        glm::vec3 get_scale();
        void get_scale(float &x, float &y, float &z);
        glm::quat get_orientation();
        WorldObject *get_parent();
        std::set<WorldObject *> get_children();
        
        World *get_root();
        
        /**
         * The model matrix can't be set explicitly and is created
         * from the other parameters. NOTE: This model matrix will
         * be in world space, **not** parent space.
         */
        glm::mat4 get_model_matrix();
        
    };
}
#endif
