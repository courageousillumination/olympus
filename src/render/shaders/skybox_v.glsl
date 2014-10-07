#version 330

layout (location = 0) in vec3 position;

uniform mat4 MVP;

out vec3 texture_coord;

void main() {
    gl_Position = (MVP * vec4(position, 1.0)).xyww;
    texture_coord = position;
}