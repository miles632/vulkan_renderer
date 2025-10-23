#extension GL_EXT_nonuniform_qualifier : require

#include "raycommon.glsl"
#include "random.glsl"


hitPayload scatterLambertian(vec3 normal, vec3 rayDir, const float distance, inout uint seed)
{
    const bool isScattered = dot(rayDir, normal) < 0;
    const vec4 colorAndDistance = vec4(vec3(1.0), distance);
    const vec4 scatter = vec4(normal + randomUnitInSphere(seed), isScattered ? 1 : 0);
    return hitPayload(colorAndDistance, scatter, seed);
}