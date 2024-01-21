#version 460 core

layout (local_size_x = 1) in;

layout (std430, binding = 3) buffer Offsets
{
    vec3 data[];
} offsets;

layout (std430, binding = 4) buffer Colors
{
    vec3 data[];
} colors;

void main() {
    int coords = int(gl_GlobalInvocationID.x);

    float a = 10.0;
    float b = 8.0 / 3.0;
    float c = 28.0;

    vec3 pos = offsets.data[coords];

    float dx = a * (pos.y - pos.x);
    float dy = pos.x * (c - pos.z) - pos.y;
    float dz = pos.x * pos.y - b * pos.z;

    pos += vec3(dx, dy, dz) * 0.001;


    offsets.data[coords] = pos;
    colors.data[coords] = normalize(vec3(dx, dy, dz)) / 2.0 + 0.5;
}