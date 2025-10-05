#version 410 core

layout (vertices = 4) out;

uniform vec3 u_viewPos;
uniform float u_radius;

float distance[];

uniform mat4 u_model;

const int MIN_TESS_LEVEL = 2;
const int MAX_TESS_LEVEL = 128;
float MIN_DISTANCE = 25;
float MAX_DISTANCE = 60;

void main() {
    if (gl_InvocationID == 0) {
        // Get position of vertices and player in world space
        vec4 worldPos00 = gl_in[0].gl_Position;
        vec4 worldPos10 = gl_in[1].gl_Position;
        vec4 worldPos01 = gl_in[2].gl_Position;
        vec4 worldPos11 = gl_in[3].gl_Position;

        worldPos00 = u_model * vec4(u_radius/length(worldPos00) * worldPos00.xyz, worldPos00.w);
        worldPos10 = u_model * vec4(u_radius/length(worldPos10) * worldPos10.xyz, worldPos10.w);
        worldPos01 = u_model * vec4(u_radius/length(worldPos01) * worldPos01.xyz, worldPos01.w);
        worldPos11 = u_model * vec4(u_radius/length(worldPos11) * worldPos11.xyz, worldPos11.w);
        vec4 cameraPos = vec4(u_viewPos, 1.0);

        // Find the distance of each vertex from player (between 0 and 1)
        float distance00 = clamp((length(cameraPos-worldPos00)-MIN_DISTANCE) / (MAX_DISTANCE-MIN_DISTANCE), 0.0, 1.0);
        float distance10 = clamp((length(cameraPos-worldPos10)-MIN_DISTANCE) / (MAX_DISTANCE-MIN_DISTANCE), 0.0, 1.0);
        float distance01 = clamp((length(cameraPos-worldPos01)-MIN_DISTANCE) / (MAX_DISTANCE-MIN_DISTANCE), 0.0, 1.0);
        float distance11 = clamp((length(cameraPos-worldPos11)-MIN_DISTANCE) / (MAX_DISTANCE-MIN_DISTANCE), 0.0, 1.0);

        // Determine how much tesselation we need depending on distance from player
        float tessLevel0 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance01, distance00));
        float tessLevel1 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance00, distance10));
        float tessLevel2 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance10, distance11));
        float tessLevel3 = mix(MAX_TESS_LEVEL, MIN_TESS_LEVEL, min(distance11, distance01));

        gl_TessLevelOuter[0] = tessLevel0;
        gl_TessLevelOuter[1] = tessLevel1;
        gl_TessLevelOuter[2] = tessLevel2;
        gl_TessLevelOuter[3] = tessLevel3;

        gl_TessLevelInner[0] = max(tessLevel1, tessLevel3);
        gl_TessLevelInner[1] = max(tessLevel0, tessLevel2);
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}