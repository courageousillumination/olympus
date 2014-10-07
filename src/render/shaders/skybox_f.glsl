#version 330

in vec3 texture_coord;

out vec4 frag_color;

uniform samplerCube skybox;

void main() {
    frag_color = texture(skybox, texture_coord);
}