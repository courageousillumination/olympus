#ifndef OLYMPUS__RENDER__RESOURCE_MANAGER
#define OLYMPUS__RENDER__RESOURCE_MANAGER
namespace olympus {
    /**
     * The ResourceManager handels all graphics related resources.
     * This is one of the main abstractions away from raw openGL.
     * It will also recycle and reuse any resources. This is implemented
     * as a singleton, so any calls to resource creation will be bottlenecked
     * at the manager.
     */
    class ResourceManager {
    private:
        ResourceManager();
        ResourceManager(ResourceManager const&);
        void operator=(ResourceManager const&);
    public:
        static ResourceManager &get_instance();
        ~ResourceManager();
        
        /**
         * Creates one of the specified resource and returns the identifier
         */
        unsigned get_resource(int type);
        
        /**
         * Creates __num__ of the specified resources and populates the
         * array with the values
         */
        void get_resource(int type, unsigned num, unsigned values[]);
        
        /**
         * Release a single resource. This may not be immediatly deleted
         */
        void release_resource(int type, unsigned id);
        
        /**
         * Release a list of resources. They may not be removed immediatly
         */
        void release_resources(int type, unsigned num, unsigned values[]);
        
        /**
         * Forces deletion of all items that are pending removal.
         */
        void flush();
    };
}

#endif
