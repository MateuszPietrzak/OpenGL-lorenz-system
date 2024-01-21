#version 460 core
layout (location = 0) in vec2 in_pos;
layout (std430, binding = 3) buffer Offsets
{
    vec3 data[];
} offsets;

layout (std430, binding = 4) buffer Colors
{
    vec3 data[];
} colors;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 color;
out vec2 local_pos;

void main() {
    mat4 translation = mat4(1.0);
    translation[3] = vec4(offsets.data[gl_InstanceID], 1.0);
    gl_Position = projection * view * translation * model * vec4(vec3(in_pos, 0.0), 1.0);
    color = colors.data[gl_InstanceID];
    local_pos = in_pos;
}