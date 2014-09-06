#version 330 core

const int MAX_LIGHT_SOURCES = 2;

uniform vec3 light_direction[MAX_LIGHT_SOURCES];
uniform int use_lights[MAX_LIGHT_SOURCES];

in vec3 f_color;
in vec3 f_normal;

out vec3 color;

const vec3 ambient_light = vec3(0.3, 0.3, 0.3);
const vec3 diffuse_light = vec3(0.7, 0.7, 0.7);

void main() {
    vec3 light = ambient_light;
    float intensity = 0;
    for (int i = 0; i < MAX_LIGHT_SOURCES; i++) {
        if (use_lights[i] == 1) {
            intensity += max(0, dot(normalize(f_normal), -light_direction[i]));
        }
    }
    light += diffuse_light * min(1.0, intensity);
    color = f_color * light;
}