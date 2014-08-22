#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;

out vec3 f_color;

void main() {
    gl_Position =  projection_matrix * model_view_matrix * vec4(position, 1.0);
    f_color = color;
}