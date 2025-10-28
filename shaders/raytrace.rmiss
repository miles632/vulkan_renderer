#version 460
#extension GL_EXT_ray_tracing : require
#extension GL_GOOGLE_include_directive : require

#include "raycommon.glsl"
#include "host_device.h"

layout(location = 0) rayPayloadInEXT hitPayload payload;

layout(push_constant) uniform _PushConstants { PushConstants pc; };

void main() {
    payload.ColorAndDistance = vec4(pc.clearColor.xyz, -1);
    payload.ScatterDir = vec4(0.0);
}