#version 330 core

const int MAX_LIGHT_SOURCES = 2;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
// Normals not used here, since they are calculated in the shader.
flat layout(location = 3) in vec2 height_map_location;


uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat4 shadow_mvp[MAX_LIGHT_SOURCES];

out vec3 f_color;
out vec3 f_normal;
out vec3 shadow_position[MAX_LIGHT_SOURCES];

// Water stuff
uniform sampler2D height_map1;
uniform vec2 height_map_offset1;

uniform sampler2D height_map2;
uniform vec2 height_map_offset2;

const ivec3 off = ivec3(-1,0,1);
const vec2 size = vec2(2.0,0.0);

void main() {
    vec3 pos = position;
    vec2 loc1 = height_map_location + height_map_offset1;
    vec2 loc2 = height_map_location + height_map_offset2;
    
    float v1 = texture(height_map1, loc1) + texture(height_map2, loc2);
    float s01 = textureOffset(height_map1, loc1, off.xy) + textureOffset(height_map2, loc2, off.xy);
    float s21 = textureOffset(height_map1, loc1, off.zy) + textureOffset(height_map2, loc2, off.zy);
    float s10 = textureOffset(height_map1, loc1, off.yx) + textureOffset(height_map2, loc2, off.yx);
    float s12 = textureOffset(height_map1, loc1, off.yz) + textureOffset(height_map2, loc2, off.yz);
    
    vec3 va = normalize(vec3(size.xy,s21-s01));
    vec3 vb = normalize(vec3(size.yx,s12-s10));
    
    vec3 normal = cross(va, vb);
    
    pos.y += v1 / 2.0;
    
    gl_Position =  projection_matrix * model_view_matrix * vec4(pos, 1.0);
    f_normal = (model_view_matrix * vec4(normal, 0.0)).xyz;
    f_color = color;
    
    for (int i = 0; i < MAX_LIGHT_SOURCES; i++) {
        shadow_position[i] = (shadow_mvp[i] * vec4(pos, 1.0)).xyz;
    }
    

}