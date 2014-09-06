#version 330 core

const int MAX_LIGHT_SOURCES = 2;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat4 shadow_mvp[MAX_LIGHT_SOURCES];

out vec3 f_color;
out vec3 f_normal;
out vec3 shadow_position[MAX_LIGHT_SOURCES];

void main() {
    gl_Position =  projection_matrix * model_view_matrix * vec4(position, 1.0);
    f_normal = (model_view_matrix * vec4(normal, 0.0)).xyz;
    f_color = color;
    
    for (int i = 0; i < MAX_LIGHT_SOURCES; i++) {
        shadow_position[i] = (shadow_mvp[i] * vec4(position, 1.0)).xyz;
    }
    

}