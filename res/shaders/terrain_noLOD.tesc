#version 410 core

layout (vertices = 4) out;

uniform vec3 u_viewPos;
uniform float u_radius;

float distance[];

uniform mat4 u_model;

const int MIN_TESS_LEVEL = 2;
const int MAX_TESS_LEVEL = 32;
float MIN_DISTANCE = 10;
float MAX_DISTANCE = u_radius/2;

void main() {
    if (gl_InvocationID == 0) {
        const float OUTER_LEVEL = 16.0; // adjust for desired smoothness
        const float INNER_LEVEL = 16.0;

        gl_TessLevelOuter[0] = OUTER_LEVEL;
        gl_TessLevelOuter[1] = OUTER_LEVEL;
        gl_TessLevelOuter[2] = OUTER_LEVEL;
        gl_TessLevelOuter[3] = OUTER_LEVEL;

        gl_TessLevelInner[0] = INNER_LEVEL;
        gl_TessLevelInner[1] = INNER_LEVEL;
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}