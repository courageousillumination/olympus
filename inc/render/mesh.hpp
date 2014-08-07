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
        unsigned _num_verts;
        unsigned _prim_type;
    public:
        Mesh(unsigned num_attributes, PrimType prim_type);
        ~Mesh();
        
        void set_vertex_attribute(unsigned attribute_number, unsigned dims,
                                  unsigned num_vertices, const float *data);
        
        void bind();
        void draw();
    };
}
#endif
