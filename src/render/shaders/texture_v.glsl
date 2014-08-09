#version 130

in vec3 position;
in vec2 tex_coord;

out vec2 f_tex_coord;

void main(){
    f_tex_coord = tex_coord;
    gl_Position.xyz = position;
    gl_Position.w = 1.0;
}