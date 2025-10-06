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
rayPayloadInEXT hitPayload ray;

layout(push_constant) uniform _PushConstants { PushConstants pc; };

layout(binding = 4) readonly buffer VertexArray {
    Vertex v[];
} vertices;
layout(binding = 5) readonly buffer IndexArray {
    uint i[];
} indices;


void main() {
    uint i0 = indices.i[gl_PrimitiveID * 3 + 0];
    uint i1 = indices.i[gl_PrimitiveID * 3 + 1];
    uint i2 = indices.i[gl_PrimitiveID * 3 + 2];

    Vertex v0 = vertices.v[i0];
    Vertex v1 = vertices.v[i1];
    Vertex v2 = vertices.v[i2];

    const vec3 barycentrics = vec3(1.0 - attribs.x - attribs.y, attribs.x, attribs.y);

    //vec3 worldPos = gl_WorldRayOriginEXT + gl_WorldRayDirectionEXT * gl_HitTEXT; // not very precise

    const vec3 pos = v0.pos * barycentrics.x + v1.pos * barycentrics.y + v2.pos * barycentrics.z;
    const vec3 worldPos = vec3(gl_ObjectToWorldEXT * vec4(pos, 1.0));

    vec3 e1 = v1.pos - v0.pos;
    vec3 e2 = v2.pos - v0.pos;
    const vec3 nrm      = normalize(cross(e1, e2));
    const vec3 worldNrm = normalize(vec3(nrm * gl_WorldToObjectEXT));

    vec3 albedo = v0.color * barycentrics.x + v1.color * barycentrics.y + v2.color * barycentrics.z;

    ray = scatterLambertian(worldNrm, worldPos, pc.lightPos, pc.lightIntensity, albedo);
}