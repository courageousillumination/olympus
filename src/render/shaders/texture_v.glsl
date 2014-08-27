#version 400

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coord;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;

out vec2 f_tex_coord;

void main(){
    gl_Position = model_view_matrix * projection_matrix * vec4(position, 1.0);
    f_tex_coord = tex_coord;
}