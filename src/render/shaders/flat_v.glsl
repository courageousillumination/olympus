#version 130

in vec3 position;
in vec3 color;

out vec3 f_color;

void main(){
    gl_Position.xyz = position;
    gl_Position.w = 1.0;
    
    f_color = color;
}