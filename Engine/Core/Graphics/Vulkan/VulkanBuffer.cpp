/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#ifdef POLLUX_DRIVER_VULKAN

#include "VulkanBuffer.hpp"

namespace Pollux::Core
{
	VkResult VulkanBuffer::Map(VkDeviceSize size, VkDeviceSize offset)
	{
		return vkMapMemory(pDevice, pMemory, offset, size, 0, &pMappedMemory);
	}

	void VulkanBuffer::Unmap()
	{
		if (pMappedMemory != nullptr)
		{
			vkUnmapMemory(pDevice, pMemory);
			pMappedMemory = nullptr;
		}
	}

	VkResult VulkanBuffer::Bind(VkDeviceSize offset)
	{
		return vkBindBufferMemory(pDevice, pHandle, pMemory, offset);
	}

	void VulkanBuffer::SetupDescriptor(VkDeviceSize size, VkDeviceSize offset)
	{
		descriptor.offset = offset;
		descriptor.buffer = pHandle;
		descriptor.range = size;
	}

	void VulkanBuffer::CopyTo(void* pData, VkDeviceSize size)
	{
		assert(pMappedMemory != nullptr);
		memcpy(pMappedMemory, pData, size);
	}

	VkResult VulkanBuffer::Flush(VkDeviceSize size, VkDeviceSize offset)
	{
		VkMappedMemoryRange mappedMemoryRange = {};
		mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedMemoryRange.memory = pMemory;
		mappedMemoryRange.offset = offset;
		mappedMemoryRange.size = size;

		return vkFlushMappedMemoryRanges(pDevice, 1, &mappedMemoryRange);
	}

	VkResult VulkanBuffer::Invalidate(VkDeviceSize size, VkDeviceSize offset)
	{
		VkMappedMemoryRange mappedMemoryRange = {};
		mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedMemoryRange.memory = pMemory;
		mappedMemoryRange.offset = offset;
		mappedMemoryRange.size = size;

		return vkInvalidateMappedMemoryRanges(pDevice, 1, &mappedMemoryRange);
	}

	void VulkanBuffer::Destroy()
	{
		if (pHandle != VK_NULL_HANDLE)
		{
			vkDestroyBuffer(pDevice, pHandle, nullptr);
		}

		if (pMemory != VK_NULL_HANDLE)
		{
			vkFreeMemory(pDevice, pMemory, nullptr);
		}
	}
}

#endif