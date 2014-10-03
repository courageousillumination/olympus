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
    public:
        ///Defines possible targets for this texture.
        enum Target {
            TEXTURE_2D,
            TEXTURE_3D,
            NONE
        };
        //Define all possible parameters and values for a texture
        enum Parameter {
            Wrap, //Will return WrapS iff WrapS == WrapT, Invalid otherwise
            WrapS,
            WrapT
        };
        
        enum ParameterValue {
            Invalid,
            Clamp,
            Repeat
        };
    private:
        ///Stores the internal id of this texture (returned by OpenGL)
        unsigned _texture_id;
        
        int _width, _height, _depth;
        Target _target;
        
        //Cache all parameters for this texture. We assume nobody modifies these
        //without our consent.
        ParameterValue _wrapS, _wrapT;
    public:
        /**
         * The default constructor should really only be used in testing
         */
        Texture();
        Texture(Target target);
        ~Texture();
        
        /**
         * Loads a specified image into a texture.
         */
        void load_image(const char *path);
        
        /**
         * Loads raw data into a texture.
         */
        void load_data(unsigned num_channels, unsigned width, unsigned height, float *data);
        
        /**
         * Catch all for setting a specified parameter on the texture.
         */
        void set_parameter(Parameter parameter, ParameterValue value);
        
        /**
         * Get a parameter off of the texture.
         */
        ParameterValue get_parameter(Parameter parameter);
        
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
