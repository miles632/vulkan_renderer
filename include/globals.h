#pragma once
#include <vector>
#include <cstdint>
#include <vulkan/vulkan.h>

extern const uint32_t WIDTH;
extern const uint32_t HEIGHT;
extern const int MAX_FRAMES_IN_FLIGHT;
extern const std::vector<const char*> validationLayers;
extern const std::vector<const char*> deviceExtensions;
extern const bool enableValidationLayers;

extern PFN_vkCreateAccelerationStructureKHR pfnCreateAccelerationStructureKHR;
extern PFN_vkGetAccelerationStructureBuildSizesKHR pfnGetAccelerationStructureBuildSizesKHR;
extern PFN_vkCmdBuildAccelerationStructuresKHR pfnCmdBuildAccelerationStructuresKHR;
extern PFN_vkDestroyAccelerationStructureKHR pfnDestroyAccelerationStructureKHR;
extern PFN_vkGetBufferDeviceAddressKHR pfnGetBufferDeviceAddressKHR;
extern PFN_vkGetAccelerationStructureDeviceAddressKHR pfnGetAccelerationStructureDeviceAddressKHR;
