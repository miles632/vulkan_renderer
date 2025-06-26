#include "globals.h"

const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = 1080;
const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
    VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
    VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
    VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
    VK_KHR_SPIRV_1_4_EXTENSION_NAME,
    VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
    VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

extern PFN_vkCreateAccelerationStructureKHR pfnCreateAccelerationStructureKHR = nullptr;
extern PFN_vkGetAccelerationStructureBuildSizesKHR pfnGetAccelerationStructureBuildSizesKHR = nullptr;
extern PFN_vkCmdBuildAccelerationStructuresKHR pfnCmdBuildAccelerationStructuresKHR = nullptr;
extern PFN_vkDestroyAccelerationStructureKHR pfnDestroyAccelerationStructureKHR = nullptr;
extern PFN_vkGetBufferDeviceAddressKHR pfnGetBufferDeviceAddressKHR = nullptr;
extern PFN_vkGetAccelerationStructureDeviceAddressKHR pfnGetAccelerationStructureDeviceAddressKHR = nullptr;