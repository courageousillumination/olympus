#ifndef OLYMPUS__RENDER__GRAPHICS_STATE_MANAGER
#define OLYMPUS__RENDER__GRAPHICS_STATE_MANAGER

#include "render/framebuffer.hpp"

namespace olympus {
    /**
     * The GraphicsState struct simply wraps all options that will
     * be passed to the lower level when it is pushed to a graphics 
     * state manager.
     */
    struct GraphicsState {
        bool wireframe;
        bool use_depth_test;
        bool cull;
        bool blend;
        int depth_function;
        int cull_face;
        Framebuffer *framebuffer;
        
        GraphicsState *next;
        
        GraphicsState();
    };
    
    /**
     * The GraphicsStateManager is a single point of access for all 
     * changes to the broad state machine that is the graphics driver.
     * This includes things like culling, wireframe, etc.
     */
    class GraphicsStateManager {
    private:
        GraphicsStateManager();
        GraphicsStateManager(GraphicsStateManager const&);
        void operator=(GraphicsStateManager const&);
        
        /**
         * This will actually apply a graphics state object. It will
         * try to be as lazy as possible, only applying if the previous
         * was different or null.
         */
        void _apply_graphics_state(GraphicsState *state);
        
        GraphicsState *_head;
    public:
        static GraphicsStateManager& get_instance();
        ~GraphicsStateManager();
        
        /**
         * The graphics state will be managed as a stack.
         */
        
        GraphicsState *get_head();
        void push(GraphicsState *state);
        void pop();
    };
    
}
#endif
