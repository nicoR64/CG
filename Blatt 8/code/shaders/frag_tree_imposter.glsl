#version 420 core

uniform sampler2D tree_sprite_tx2D;

layout(location = 1) in vec2 uv;

layout(location = 0) out vec4 out_color;

void main() {
    // TODO 2.4
    // set out_color to value retrieved from texture
    out_color = vec4(uv,0.0,1.0);
    // if alpha value is below a threshold, discard the fragment
    // experiment with different thresholds and find one that yield
    // visually pleasing results
}
