#version 460
#extension GL_EXT_scalar_block_layout : enable
#extension GL_GOOGLE_include_directive : enable
#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
#extension GL_EXT_buffer_reference2 : require
#extension GL_EXT_ray_tracing : require

#include "raycommon.glsl"
#include "host_device.h"
#include "scatter.glsl"

hitAttributeEXT vec2 attribs;
layout(location = 0) rayPayloadInEXT hitPayload payload;

layout(push_constant) uniform _PushConstants { PushConstants pc; };

layout(binding = 4) readonly buffer VertexArray {
    Vertex v[];
} vertices;
layout(binding = 5) readonly buffer IndexArray {
    uint i[];
} indices;
layout(binding = 6) readonly buffer OffsetArray {
    uvec2 o[];
} offsets;

vec3 Mix(vec3 a, vec3 b, vec3 c, vec3 barycentrics)
{
    return a * barycentrics.x + b * barycentrics.y + c * barycentrics.z;
}

void main() {
    const uvec2 offs = offsets.o[gl_InstanceCustomIndexEXT];
    const uint indexOffsets = offs.y;
    const uint vertexOffsets = offs.x;

    uint i0 = indices.i[indexOffsets + gl_PrimitiveID * 3 + 0];
    uint i1 = indices.i[indexOffsets + gl_PrimitiveID * 3 + 1];
    uint i2 = indices.i[indexOffsets + gl_PrimitiveID * 3 + 2];

    Vertex v0 = vertices.v[vertexOffsets + i0];
    Vertex v1 = vertices.v[vertexOffsets + i1];
    Vertex v2 = vertices.v[vertexOffsets + i2];

    vec3 barycentrics = vec3(1.0 - attribs.x - attribs.y, attribs.x, attribs.y);

    vec3 normal = normalize(Mix(
        v0.normal, v1.normal, v2.normal, barycentrics
        )
    );

    payload = scatterLambertian(normal, gl_WorldRayDirectionEXT, gl_HitTEXT, payload.RandomSeed);
}