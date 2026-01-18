#version 420 core

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
layout(location = 1) in vec3 in_color;

layout(location = 1) out vec3 frag_color;

void main() {
    // TODO 1.4
    // calculate view * model
    mat4 model_view = per_frame.view;

    // TODO 1.5
    // keep the x-axis. the y-axis shall be transformed as usual and we can ignore the z-axis,
    // because in_pos.z = 0
    // Note! Only works for a limited set of camera transformations!

    // output
    gl_Position = per_frame.proj * model_view * vec4(in_pos, 1);
    frag_color = in_color;
}
