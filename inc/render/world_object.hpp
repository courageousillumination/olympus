#ifndef OLYMPUS__RENDER__WORLD_OBJECT
#define OLYMPUS__RENDER__WORLD_OBJECT

#include <set>

#include <glm/glm.hpp>

namespace olympus {
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
        //mglm::quat _orientation;
        glm::mat4 _model_matrix;
        
        WorldObject *_parent;
        std::set<WorldObject *> _children;
    public:
        
        ///NOTE: All setters are declared virtual to allow
        ///subclasses to insert their own callbacks.
        ///NOTE: For getters and setters we provide the ability
        /// to use both glm primatives and raw floats
        virtual void set_position(glm::vec3 position);
        virtual void set_position(float x, float y, float z);
        virtual void set_scale(glm::vec3 scale);
        virtual void set_scale(float x, float y, float z);
        //TODO: Orientation setters
        virtual void set_parent(WorldObject *parent);
        virtual void add_child(WorldObject *child);
        
        glm::vec3 get_position();
        void get_position(float &x, float &y, float &z);
        glm::vec3 get_scale();
        void get_scale(float &x, float &y, float &z);
        //TODO: Orientation getters
        WorldObject *get_parent();
        std::set<WorldObject *> get_children();
        
        /**
         * The model matrix can't be set explicitly and is created
         * from the other parameters. NOTE: This model matrix will
         * be in world space, **not** parent space.
         */
        glm::mat4 get_model_matrix();
        
    };
}
#endif
