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
		return vkMapMemory(pDevice, pMemory, offset, size, 0, &pMapped);
	}

	void VulkanBuffer::Unmap()
	{
		if (pMapped != nullptr)
		{
			vkUnmapMemory(pDevice, pMemory);
			pMapped = nullptr;
		}
	}

	VkResult VulkanBuffer::Bind(VkDeviceSize offset)
	{
		return vkBindBufferMemory(pDevice, pBuffer, pMemory, offset);
	}

	void VulkanBuffer::SetupDescriptor(VkDeviceSize size, VkDeviceSize offset)
	{
		descriptor.offset = offset;
		descriptor.buffer = pBuffer;
		descriptor.range = size;
	}

	void VulkanBuffer::CopyTo(void* pData, VkDeviceSize size)
	{
		assert(pMapped != nullptr);
		memcpy(pMapped, pData, size);
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
		VkMappedMemoryRange mappedRange = {};
		mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		mappedRange.memory = pMemory;
		mappedRange.offset = offset;
		mappedRange.size = size;

		return vkInvalidateMappedMemoryRanges(pDevice, 1, &mappedRange);
	}

	void VulkanBuffer::Destroy()
	{
		if (pBuffer != VK_NULL_HANDLE)
		{
			vkDestroyBuffer(pDevice, pBuffer, nullptr);
		}

		if (pMemory != VK_NULL_HANDLE)
		{
			vkFreeMemory(pDevice, pMemory, nullptr);
		}
	}
}

#endif