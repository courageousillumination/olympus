#ifndef OLYMPUS__RENDER__TEXTURE
#define OLYMPUS__RENDER__TEXTURE
namespace olympus {
    //Forward declerations for friends
    class Framebuffer;
    
    /**
     * This represents a texture in the underlying
     * graphics system.
     */
    class Texture {
    private:
        ///Stores the internal id of this texture (returned by OpenGL)
        unsigned _texture_id;
    public:
        ///Defines possible targets for this texture.
        enum Target {
            TEXTURE_2D
        };
        
        Texture(Target target);
        ~Texture();
        
        /**
         * Bind this texture. All future texture operations will affect
         * this texture until something else is bound (either explicitly
         * or implicitly).
         */
        void bind();
        
        /**
         * We set the Framebuffer as a friend because the framebuffer needs
         * to attach textures to itself and requires acccess to the underlying id.
         */
        friend Framebuffer;
    };
}
#endif
