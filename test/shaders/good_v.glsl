#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

uniform vec3  vec3_uniform;
uniform vec2  vec2_uniform;
uniform float float_uniform;
uniform int   int_uniform;
uniform mat4  mat4_uniform;

uniform vec3  vec3_uniforms[2];
uniform vec2  vec2_uniforms[2];
uniform float float_uniforms[2];
uniform int   int_uniforms[2];
uniform mat4  mat4_uniforms[2];

out vec3 f_color;

void main(){
    //Force them not to optimize away my uniforms
    gl_Position.xyz = position + vec3_uniform[0] + vec2_uniform[0] + float_uniform + int_uniform + mat4_uniform[0][0] + 
                      vec3_uniforms[0][0] + vec2_uniforms[0][0] + float_uniforms[0] + int_uniforms[0] + mat4_uniforms[0][0][0];
    gl_Position.w = 1.0;
    
    f_color = color;
}