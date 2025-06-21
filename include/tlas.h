#pragma once

#include "vulkan/vulkan.h"
#include <vector>

struct TlasInstance {
    VkTransformMatrixKHR transform;
    uint32_t instanceCustomIndex : 24;
    uint32_t mask : 8;
    uint32_t instanceShaderBindingTableRecordOffset : 24;
    uint32_t flags;
    uint64_t blasDeviceAddress;
};

class Tlas {
public:
    VkAccelerationStructureKHR handle = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VkBuffer buffer = VK_NULL_HANDLE;

    void create(VkDevice device,
                VkPhysicalDevice physicalDevice,
                VkCommandBuffer cmdBuf,
                const std::vector<TlasInstance>& instances);

    void destroy(VkDevice device);
};