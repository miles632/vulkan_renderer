#ifdef __cplusplus
    #include <glm/glm.hpp>
    #define VEC2 glm::vec2
    #define VEC3 glm::vec3
    #define MAT4 glm::mat4
#else
    #define VEC2 vec2
    #define VEC3 vec3
    #define MAT4 mat4
#endif

struct Vertex {
    VEC3 pos;
    VEC3 color;
    VEC2 tex;
};

struct UniformBufferObject {
    MAT4 model;
    MAT4 view;
    MAT4 proj;
};

struct PushConstants {
    MAT4 viewInverse;
    MAT4 projInverse;
    VEC3 cameraPos;
    uint frameIndex;
    vec4 clearColor;
    VEC3 lightPos;
    float lightIntensity;
    int lightType;
};