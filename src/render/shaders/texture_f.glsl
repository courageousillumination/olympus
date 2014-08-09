#version 330 core

in vec2 f_tex_coord;
out vec3 color;

uniform sampler2D texture_sampler;
 
void main() {
    //color = vec3(f_tex_coord, 1.0);
    color = texture(texture_sampler, f_tex_coord).rgb;
}