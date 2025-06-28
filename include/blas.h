#pragma once

#include "vertex.h"
#include "vulkan/vulkan.h"
#include "renderer.h"

struct BlasInput {
    VkDeviceAddress vertexAddress;
    const uint32_t vertexStride = sizeof(Vertex);
    uint32_t vertexCount;
    VkDeviceAddress indexAddress;
    uint32_t indexCount;
    VkFormat vertexFormat;
};

class Blas {
public:
    VkAccelerationStructureKHR handle = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VkBuffer buffer = VK_NULL_HANDLE;

    void create(VkDevice device,
                VkCommandBuffer cmdBuf,
                const BlasInput& input,
                Renderer* state);

    void destroy(VkDevice device);
};