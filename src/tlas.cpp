#include "tlas.h"

void Tlas::create(VkDevice device,
                  VkPhysicalDevice physicalDevice,
                  VkCommandBuffer cmdBuf,
                  const std::vector<TlasInstance>& instances,
                  Renderer* state
                  ) {

    std::vector<VkAccelerationStructureInstanceKHR> vkInstances;
    for (const auto& inst : instances) {
        VkAccelerationStructureInstanceKHR vkInst{};
        vkInst.transform = inst.transform;
        vkInst.instanceCustomIndex = inst.instanceCustomIndex;
        vkInst.mask = inst.mask;
        vkInst.instanceShaderBindingTableRecordOffset = inst.instanceShaderBindingTableRecordOffset;
        vkInst.flags = inst.flags;
        vkInst.accelerationStructureReference = inst.blasDeviceAddress;
        vkInstances.push_back(vkInst);
    }

    VkBuffer instancesBuffer;
    VkDeviceMemory instancesBufferMemory;

    state->createBuffer(
        (VkDeviceSize)instances.size(),
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
        VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR,
        0,
        instancesBuffer,
        instancesBufferMemory
    );

    VkAccelerationStructureBuildGeometryInfoKHR geometryInfo;
    geometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    geometryInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
    geometryInfo.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    geometryInfo.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
    geometryInfo.geometryCount = 1;
    geometryInfo.pGeometries = nullptr;

    uint32_t primitiveCount = static_cast<uint32_t>(1);

    VkAccelerationStructureCreateInfoKHR structureInfo;
    structureInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
    structureInfo.buffer = NULL;

    /*
    VkCmdBuildAccelerationStructuresKHR(
        cmdBuf,

    );
    */
}

void Tlas::destroy(VkDevice device) {

}