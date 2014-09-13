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
    public:
        enum ResourceType {
            TEXTURE,
            VERTEX_ARRAY,
            BUFFER,
            FRAMEBUFFER
        };
    private:
        ResourceManager();
        ResourceManager(ResourceManager const&);
        void operator=(ResourceManager const&);
        
        // Some quick and dirty memory leak detection. We count all allocations and all 
        // frees. If they don't match up we print a warning.
        unsigned long _num_allocs, _num_frees;
    public:
        static ResourceManager &get_instance();
        ~ResourceManager();
        
        /**
         * Creates one of the specified resource and returns the identifier
         */
        unsigned get_resource(ResourceType type);
        
        /**
         * Creates __num__ of the specified resources and populates the
         * array with the values
         */
        void get_resources(ResourceType type, unsigned num, unsigned values[]);
        
        /**
         * Release a single resource. This may not be immediatly deleted
         */
        void release_resource(ResourceType type, unsigned id);
        
        /**
         * Release a list of resources. They may not be removed immediatly
         */
        void release_resources(ResourceType type, unsigned num, unsigned values[]);
        
        // Some function to manage memory
        /**
         * This function is intended to check if anything is currently allocated. If it is
         * it will print an error message.
         */
        void check_allocation();
    };
}

#endif
