#version 460
#extension GL_EXT_ray_tracing : require
#extension GL_GOOGLE_include_directive : require

#include "raycommon.glsl"
#include "host_device.h"

layout(location = 0) rayPayloadInEXT hitPayload payload;

layout(push_constant) uniform _PushConstants { PushConstants pc; };

void main() {
    payload.Color = pc.clearColor.xyz * 0.8;
}