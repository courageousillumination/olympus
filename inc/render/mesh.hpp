#ifndef OLYMPUS__RENDER__MESH
#define OLYMPUS__RENDER__MESH
namespace olympus {
    /**
     * A mesh is a class based wrapper around a vertex array object.
     */
    class Mesh {
    public:
        enum PrimType {
            TRIANGLES,
            TRIANGLE_STRIP,
            TRIANGLE_FAN,
        };
    private:
        unsigned _vao_id;
        unsigned *_attributes;
        unsigned _num_attributes;
        unsigned _num_verts;
        unsigned _prim_type;
        unsigned _element_buffer;
        unsigned _num_indices;
        bool _indexed;
    public:
        Mesh(unsigned num_attributes, PrimType prim_type);
        ~Mesh();
        
        /**
         * Sets a vertex attribute using the given list of data.
         */
        void set_vertex_attribute(unsigned attribute_number, unsigned dims,
                                  unsigned num_vertices, const float *data);
        
        /**
         * If this is called with a non null array then the mesh will be
         * converted into an indexed mesh.
         */
        void set_indices(unsigned num_indices, const unsigned *indices);
        
        /**
         * Bind this mesh to the current render context. All meshes
         * must be bound before they can be drawn.
         */
        void bind();
        
        /**
         * Draw the specified mesh.
         */
        void draw();
    };
}
#endif
