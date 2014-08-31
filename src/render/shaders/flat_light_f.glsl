#version 330 core

uniform vec3 light_direction;

in vec3 f_color;
in vec3 f_normal;

out vec3 color;

const vec3 ambient_light = vec3(0.3, 0.3, 0.3);
const vec3 diffuse_light = vec3(0.7, 0.7, 0.7);

void main() {
    vec3 light = ambient_light;
    float intensity = max(0, dot(normalize(f_normal), -light_direction));
    light += diffuse_light * intensity;
    color = f_color * light;
}