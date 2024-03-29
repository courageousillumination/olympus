#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;

out vec3 f_color;
out vec3 f_normal;

void main() {
    gl_Position =  projection_matrix * model_view_matrix * vec4(position, 1.0);
    f_normal = (model_view_matrix * vec4(normal, 0.0)).xyz;
    f_color = color;

}