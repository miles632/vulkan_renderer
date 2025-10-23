#ifndef COMMON_GLSL
#define COMMON_GLSL

struct hitPayload {
    vec4 ColorAndDistance;
    vec4 ScatterDir;
    uint RandomSeed;
};

#endif