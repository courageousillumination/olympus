#version 330 core

const int MAX_LIGHT_SOURCES = 2;

uniform vec3 light_direction[MAX_LIGHT_SOURCES];
uniform int use_lights[MAX_LIGHT_SOURCES];

uniform sampler2D shadow_map[MAX_LIGHT_SOURCES];

in vec3 f_color;
in vec3 f_normal;
in vec3 shadow_position[MAX_LIGHT_SOURCES];

out vec3 color;

const vec3 ambient_light = vec3(0.3, 0.3, 0.3);
const vec3 diffuse_light = vec3(0.7, 0.7, 0.7);

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

const float bias = 0.005;

void main() {
    vec3 light = ambient_light;
    float intensity = 0;
    float visibility;
    for (int i = 0; i < MAX_LIGHT_SOURCES; i++) {
        if (use_lights[i] == 1) {
            visibility = 1.0;
            for (int j=0;j<4;j++){
                if ( texture2D(shadow_map[i], shadow_position[i].xy + poissonDisk[j]/700.0 ).z  <  shadow_position[i].z-bias ){
                    visibility-=0.2;
                }
            }
            intensity += visibility * max(0, dot(normalize(f_normal), -light_direction[i]));
        }
    }
    light += diffuse_light * intensity;
    color = f_color * light;
}