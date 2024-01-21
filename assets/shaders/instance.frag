#version 460 core

out vec4 frag_col;
in vec3 color;
in vec2 local_pos;

void main() {
    if(length(local_pos) > 0.5) {
        discard;
    }
    frag_col = vec4(color, 1.0);
}