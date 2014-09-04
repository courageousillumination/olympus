#version 330 core

uniform vec3 light_direction;
uniform sampler2D shadow_map;

in vec3 f_color;
in vec3 f_normal;
in vec3 shadow_position;

out vec3 color;

const vec3 ambient_light = vec3(0.3, 0.3, 0.3);
const vec3 diffuse_light = vec3(0.7, 0.7, 0.7);

void main() {
    vec3 light = ambient_light;
    if (texture(shadow_map, shadow_position.xy).r >= shadow_position.z - 0.005) {
        float intensity = max(0, dot(normalize(f_normal), -light_direction));
        light += diffuse_light * intensity;
    }
    color = f_color * light;
}