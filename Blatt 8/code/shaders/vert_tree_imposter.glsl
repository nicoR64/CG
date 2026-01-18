#version 440 core

layout(binding = 0) uniform PerFrame {
    mat4 view; // world coords -> camera coords
    mat4 proj; // camera coords -> clip coords
}
per_frame;

layout(binding = 1) uniform Trees {
    mat4 model[192]; // object coords -> world coords
}
trees;

layout(location = 0) in vec3 in_pos; // position in object coords
layout(location = 1) in vec3 in_uv;  // uv coordinates for texture mapping

layout(location = 1) out vec2 uv;

// Calculates a pseudo random number in [0, 1]
float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    // TODO 2.2 
    // reuse your solution from vert_trees.glsl!
    mat4 model_view; // = ...

    // TODO 2.5
    // for a more convicing result, compute a random number between 0.7 and 1.0 to scale the tree vertices
    // use the supplied function rand with the tree's xz position in the scene as input

    // output
    gl_Position = per_frame.proj * model_view * vec4(in_pos, 1);
    uv = in_uv.rg;
}
