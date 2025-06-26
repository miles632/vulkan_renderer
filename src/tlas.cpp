#include "tlas.h"
#include "globals.h"

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

    auto instancesBufferSize = static_cast<VkDeviceSize>(vkInstances.size() * sizeof(VkAccelerationStructureInstanceKHR));

    state->createBuffer(
        //static_cast<VkDeviceSize>(instances.size() * sizeof(VkAccelerationStructureKHR)),
        instancesBufferSize,
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
        VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR |
        VK_BUFFER_USAGE_TRANSFER_DST_BIT, // for memcpy
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        instancesBuffer,
        instancesBufferMemory
    );

    void *instancesMap;
    vkMapMemory(state->device, instancesBufferMemory, 0, instancesBufferSize, 0, &instancesMap);
    memcpy(instancesMap, vkInstances.data(), instancesBufferSize);
    vkUnmapMemory(state->device, instancesBufferMemory);

    VkBufferDeviceAddressInfoKHR instanceAddressInfo{};
    instanceAddressInfo.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
    instanceAddressInfo.buffer = instancesBuffer;
    VkDeviceAddress instancesBufferDeviceAddress = vkGetBufferDeviceAddress(state->device ,&instanceAddressInfo);

    VkAccelerationStructureGeometryKHR tlasGeometry{};
    tlasGeometry.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
    tlasGeometry.geometryType = VK_GEOMETRY_TYPE_INSTANCES_KHR;
    tlasGeometry.flags = VK_GEOMETRY_OPAQUE_BIT_KHR;
    tlasGeometry.geometry.instances.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
    tlasGeometry.geometry.instances.arrayOfPointers = VK_FALSE;
    tlasGeometry.geometry.instances.data.deviceAddress = instancesBufferDeviceAddress;

    VkAccelerationStructureBuildGeometryInfoKHR geometryInfo;
    geometryInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
    geometryInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
    geometryInfo.flags = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR;
    geometryInfo.mode = VK_BUILD_ACCELERATION_STRUCTURE_MODE_BUILD_KHR;
    geometryInfo.geometryCount = 1;
    geometryInfo.pGeometries = &tlasGeometry;

    auto primitiveCount = static_cast<uint32_t>(vkInstances.size());

    VkAccelerationStructureBuildSizesInfoKHR tlasSizeInfo{};
    tlasSizeInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;

    pfnGetAccelerationStructureBuildSizesKHR(
        state->device,
        VK_ACCELERATION_STRUCTURE_BUILD_TYPE_DEVICE_KHR,
        &geometryInfo,
        &primitiveCount,
        &tlasSizeInfo
        );

    VkBuffer tlasBuffer;
    VkDeviceMemory tlasBufferMemory;
    state->createBuffer(
        tlasSizeInfo.accelerationStructureSize,
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT | VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        tlasBuffer,
        tlasBufferMemory
        );

    VkAccelerationStructureCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
    createInfo.buffer = tlasBuffer;
    createInfo.size = tlasSizeInfo.accelerationStructureSize;
    createInfo.offset = 0;
    createInfo.type = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR;
    createInfo.deviceAddress = 0;
    createInfo.createFlags = 0; // no flags needed, for now

    VkAccelerationStructureKHR createdTlas;
    pfnCreateAccelerationStructureKHR(
        state->device,
        &createInfo,
        nullptr,
        &createdTlas
        );

    this->handle = createdTlas;

    VkBuffer scratchBuffer;
    VkDeviceMemory scratchBufferMemory;
    state->createBuffer(
        tlasSizeInfo.buildScratchSize,
        VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        scratchBuffer,
        scratchBufferMemory
        );

    
    VkBufferDeviceAddressInfo scratchDeviceAddressInfo;
    scratchDeviceAddressInfo.sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
    scratchDeviceAddressInfo.buffer = scratchBuffer;
    VkDeviceAddress scratchDeviceAddress = vkGetBufferDeviceAddress(state->device, &scratchDeviceAddressInfo);


    geometryInfo.dstAccelerationStructure = this->handle;
    geometryInfo.scratchData.deviceAddress = scratchDeviceAddress;

    VkAccelerationStructureBuildRangeInfoKHR rangeInfo{};
    rangeInfo.primitiveCount = primitiveCount;
    rangeInfo.primitiveOffset = 0;
    rangeInfo.firstVertex = 0;
    rangeInfo.transformOffset = 0;

    const VkAccelerationStructureBuildRangeInfoKHR* pBuildRangeInfos[] = { &rangeInfo };

    pfnCmdBuildAccelerationStructuresKHR(
        cmdBuf,
        1,
        &geometryInfo,
        pBuildRangeInfos
        );
}

void Tlas::destroy(VkDevice device) {

}