#version 460 core

out vec4 frag_col;
in vec3 color;

void main() {
    frag_col = vec4(color, 1.0);
}