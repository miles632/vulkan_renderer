#extension GL_EXT_nonuniform_qualifier : require

#include "raycommon.glsl"

hitPayload scatterLambertian(vec3 worldSurfaceNormal, vec3 worldHitPos, vec3 lightPos, float lightIntensity, vec3 albedo) {
    vec3 L =  normalize(lightPos - worldHitPos);
    float NdotL = max(dot(worldSurfaceNormal, L), 0);
    vec3 RDiffuse = albedo * NdotL * lightIntensity;

    hitPayload payload;
    payload.Color = RDiffuse;
    payload.Distance = uint(length(lightPos - worldHitPos));
    payload.ScatterDir = vec4(L, 0.0);

    return payload;
}