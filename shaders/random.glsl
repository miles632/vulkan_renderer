uint hash(vec2 p) {
    uvec3 v = uvec3(floatBitsToUint(p.x), floatBitsToUint(p.y), 0u);
    v = v * 1664525u + 1013904223u;
    v.x += v.y * v.z;
    v.y += v.z * v.x;
    v.z += v.x * v.y;
    return v.x ^ v.y ^ v.z;
}

uint randomInt(inout uint seed) {
    seed = 1664525u * seed + 1013904223u;
    return seed;
}

float randomFloat(inout uint seed) {
    return (float(randomInt(seed) & 0x00FFFFFFu) / float(0x01000000u));

}

vec3 randomUnitInSphere(inout uint seed) {
    while (true) {
        vec3 p = 2 * vec3(randomFloat(seed), randomFloat(seed), randomFloat(seed)) - 1;

        if(dot(p, p) < 1) {
            return p;
        }
    }
}

vec2 randomUnitInDisk(inout uint seed) {
    while (true) {
        vec2 p = 2.0 * vec2(randomFloat(seed), randomFloat(seed)) - 1.0;
        if (dot(p, p) < 1.0) return p;
    }
}