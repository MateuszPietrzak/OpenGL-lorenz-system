#version 460 core
layout (location = 0) in vec2 in_pos;
layout (std430, binding = 3) buffer Offsets
{
    vec3 data[];
} offsets;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 color;

void main() {
    mat4 translation = mat4(1.0);
    translation[3] = vec4(offsets.data[gl_InstanceID], 1.0);
    gl_Position = projection * view * translation * model * vec4(vec3(in_pos, 0.0), 1.0);
    color = (offsets.data[gl_InstanceID] / 120.0) + 0.3;
}