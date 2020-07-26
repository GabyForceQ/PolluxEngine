/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#ifdef POLLUX_DRIVER_VULKAN

#include "VulkanDevice.hpp"
#include "VulkanBuffer.hpp"
#include "VulkanBase.hpp"
#include "Engine/Core/Generic/GenericUtils.hpp"

namespace Pollux::Core
{
	VulkanDevice::VulkanDevice(VkPhysicalDevice pPhysicalDevice)
	{
		assert(pPhysicalDevice != nullptr);
		physicalDevice.pHandle = pPhysicalDevice;
		physicalDevice.FillFeaturesAndProperties();

		uint32_t queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice, &queueFamilyCount, nullptr);
		
		assert(queueFamilyCount > 0u);
		
		queueFamilyProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(pPhysicalDevice, &queueFamilyCount, queueFamilyProperties.data());

		uint32_t extensionCount = 0u;
		vkEnumerateDeviceExtensionProperties(pPhysicalDevice, nullptr, &extensionCount, nullptr);

		if (extensionCount > 0u)
		{
			std::vector<VkExtensionProperties> extensions(extensionCount);
			
			if (vkEnumerateDeviceExtensionProperties(pPhysicalDevice, nullptr, &extensionCount, &extensions.front()) == VK_SUCCESS)
			{
				for (auto extension : extensions)
				{
					supportedExtensions.push_back(extension.extensionName);
				}
			}
		}
	}

	VulkanDevice::~VulkanDevice()
	{
		if (pCommandPool != VK_NULL_HANDLE)
		{
			vkDestroyCommandPool(pLogicalDevice, pCommandPool, nullptr);
		}

		if (pLogicalDevice != VK_NULL_HANDLE)
		{
			vkDestroyDevice(pLogicalDevice, nullptr);
		}
	}

	uint32_t VulkanDevice::GetMemoryType(uint32_t typeBits, VkMemoryPropertyFlags memoryPropertyFlags, VkBool32* pMemoryTypeFound)
	{
		for (uint32_t i = 0u; i < physicalDevice.memoryProperties.memoryTypeCount; i++)
		{
			if ((typeBits & 1u) == 1u)
			{
				if ((physicalDevice.memoryProperties.memoryTypes[i].propertyFlags & memoryPropertyFlags) == memoryPropertyFlags)
				{
					if (pMemoryTypeFound != nullptr)
					{
						*pMemoryTypeFound = true;
					}

					return i;
				}
			}

			typeBits >>= 1u;
		}

		if (pMemoryTypeFound != nullptr)
		{
			*pMemoryTypeFound = false;
			return 0u;
		}
		else
		{
			throw std::runtime_error("Error (Vulkan): Couldn't find a matching video device memory type.");
		}
	}

	uint32_t VulkanDevice::GetQueueFamilyIndex(VkQueueFlagBits queueFlagBits)
	{
		if (queueFlagBits & VK_QUEUE_COMPUTE_BIT)
		{
			for (uint32_t i = 0u; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++)
			{
				if ((queueFamilyProperties[i].queueFlags & queueFlagBits)
					&& ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0u))
				{
					return i;
					break;
				}
			}
		}

		if (queueFlagBits & VK_QUEUE_TRANSFER_BIT)
		{
			for (uint32_t i = 0u; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++)
			{
				if ((queueFamilyProperties[i].queueFlags & queueFlagBits)
					&& ((queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0u)
					&& ((queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0u))
				{
					return i;
					break;
				}
			}
		}

		for (uint32_t i = 0u; i < static_cast<uint32_t>(queueFamilyProperties.size()); i++)
		{
			if (queueFamilyProperties[i].queueFlags & queueFlagBits)
			{
				return i;
				break;
			}
		}

		throw std::runtime_error("Error (Vulkan): Couldn't find a matching queue family index.");
	}

	VkFormat VulkanDevice::GetSupportedDepthFormat(bool bCheckSamplingSupport)
	{
		std::vector<VkFormat> depthFormats =
		{
			VK_FORMAT_D32_SFLOAT_S8_UINT,
			VK_FORMAT_D32_SFLOAT,
			VK_FORMAT_D24_UNORM_S8_UINT,
			VK_FORMAT_D16_UNORM_S8_UINT,
			VK_FORMAT_D16_UNORM
		};

		for (auto& format : depthFormats)
		{
			VkFormatProperties formatProperties;
			vkGetPhysicalDeviceFormatProperties(physicalDevice.pHandle, format, &formatProperties);

			if (formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
			{
				if (bCheckSamplingSupport)
				{
					if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT))
					{
						continue;
					}
				}

				return format;
			}
		}
		throw std::runtime_error("Error (Vulkan): Couldn't find a matching depth format.");
	}

	VkResult VulkanDevice::CreateLogicalDevice(VkPhysicalDeviceFeatures enabledFeatures,
		std::vector<const char*> pEnabledExtensions, void* pNextChain, bool bUseSwapChain,
		VkQueueFlags requestedQueueTypes)
	{
		std::vector<const char*> deviceExtensions(pEnabledExtensions);
		std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfos = {};
		const float defaultQueuePriority = 0.f;

		if (requestedQueueTypes & VK_QUEUE_GRAPHICS_BIT)
		{
			queueFamilyIndices.graphics = GetQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);

			VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
			deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndices.graphics;
			deviceQueueCreateInfo.queueCount = 1u;
			deviceQueueCreateInfo.pQueuePriorities = &defaultQueuePriority;

			deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
		}
		else
		{
			queueFamilyIndices.graphics = VK_NULL_HANDLE;
		}

		if (requestedQueueTypes & VK_QUEUE_COMPUTE_BIT)
		{
			queueFamilyIndices.compute = GetQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);
			
			if (queueFamilyIndices.compute != queueFamilyIndices.graphics)
			{
				VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
				deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndices.compute;
				deviceQueueCreateInfo.queueCount = 1u;
				deviceQueueCreateInfo.pQueuePriorities = &defaultQueuePriority;
				
				deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
			}
		}
		else
		{
			queueFamilyIndices.compute = queueFamilyIndices.graphics;
		}

		if (requestedQueueTypes & VK_QUEUE_TRANSFER_BIT)
		{
			queueFamilyIndices.transfer = GetQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);
			
			if ((queueFamilyIndices.transfer != queueFamilyIndices.graphics)
				&& (queueFamilyIndices.transfer != queueFamilyIndices.compute))
			{
				VkDeviceQueueCreateInfo deviceQueueCreateInfo = {};
				deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
				deviceQueueCreateInfo.queueFamilyIndex = queueFamilyIndices.transfer;
				deviceQueueCreateInfo.queueCount = 1u;
				deviceQueueCreateInfo.pQueuePriorities = &defaultQueuePriority;

				deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
			}
		}
		else
		{
			queueFamilyIndices.transfer = queueFamilyIndices.graphics;
		}

		
		if (bUseSwapChain)
		{
			deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		}

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(deviceQueueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = deviceQueueCreateInfos.data();
		deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

		VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = {};

		if (pNextChain != nullptr)
		{
			physicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
			physicalDeviceFeatures2.features = enabledFeatures;
			physicalDeviceFeatures2.pNext = pNextChain;

			deviceCreateInfo.pEnabledFeatures = nullptr;
			deviceCreateInfo.pNext = &physicalDeviceFeatures2;
		}

		if (IsExtensionSupported(VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
		{
			deviceExtensions.push_back(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
			bEnableDebugMarkers = true;
		}

		if (deviceExtensions.size() > 0u)
		{
			deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
			deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
		}

		VkResult result = vkCreateDevice(physicalDevice.pHandle, &deviceCreateInfo, nullptr, &pLogicalDevice);

		if (result == VK_SUCCESS)
		{
			pCommandPool = CreateCommandPool(queueFamilyIndices.graphics);
		}

		physicalDevice.enabledFeatures = enabledFeatures;

		return result;
	}

	VkResult VulkanDevice::CreateBuffer(VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags memoryPropertyFlags,
		VkDeviceSize bufferSize, VkBuffer* pBuffer, VkDeviceMemory* pDeviceMemory, void* pData)
	{
		VkBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.usage = bufferUsageFlags;
		bufferCreateInfo.size = bufferSize;
		bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VulkanCheckResult(vkCreateBuffer(pLogicalDevice, &bufferCreateInfo, nullptr, pBuffer));

		VkMemoryRequirements memoryRequirements = {};

		VkMemoryAllocateInfo memoryAllocateInfo = {};
		memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		vkGetBufferMemoryRequirements(pLogicalDevice, *pBuffer, &memoryRequirements);

		memoryAllocateInfo.allocationSize = memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = GetMemoryType(memoryRequirements.memoryTypeBits, memoryPropertyFlags);
		
		VulkanCheckResult(vkAllocateMemory(pLogicalDevice, &memoryAllocateInfo, nullptr, pDeviceMemory));

		if (pData != nullptr)
		{
			void* mapped;
			
			VulkanCheckResult(vkMapMemory(pLogicalDevice, *pDeviceMemory, 0u, bufferSize, 0u, &mapped));
			
			memcpy(mapped, pData, bufferSize);

			if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0u)
			{
				VkMappedMemoryRange mappedMemoryRange = {};
				mappedMemoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
				mappedMemoryRange.memory = *pDeviceMemory;
				mappedMemoryRange.offset = 0u;
				mappedMemoryRange.size = bufferSize;
				
				vkFlushMappedMemoryRanges(pLogicalDevice, 1u, &mappedMemoryRange);
			}

			vkUnmapMemory(pLogicalDevice, *pDeviceMemory);
		}

		VulkanCheckResult(vkBindBufferMemory(pLogicalDevice, *pBuffer, *pDeviceMemory, 0u));

		return VK_SUCCESS;
	}

	VkResult VulkanDevice::CreateBuffer(VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags memoryPropertyFlags,
		VulkanBuffer* pBuffer, VkDeviceSize bufferSize, void* pData)
	{
		pBuffer->pDevice = pLogicalDevice;

		VkBufferCreateInfo bufferCreateInfo = {};
		bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferCreateInfo.usage = bufferUsageFlags;
		bufferCreateInfo.size = bufferSize;

		VulkanCheckResult(vkCreateBuffer(pLogicalDevice, &bufferCreateInfo, nullptr, &pBuffer->pHandle));

		VkMemoryRequirements memoryRequirements = {};

		VkMemoryAllocateInfo memoryAllocateInfo = {};
		memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		
		vkGetBufferMemoryRequirements(pLogicalDevice, pBuffer->pHandle, &memoryRequirements);
		
		memoryAllocateInfo.allocationSize = memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = GetMemoryType(memoryRequirements.memoryTypeBits, memoryPropertyFlags);
		
		VulkanCheckResult(vkAllocateMemory(pLogicalDevice, &memoryAllocateInfo, nullptr, &pBuffer->pMemory));

		pBuffer->alignment = memoryRequirements.alignment;
		pBuffer->size = bufferSize;
		pBuffer->usageFlags = bufferUsageFlags;
		pBuffer->memoryPropertyFlags = memoryPropertyFlags;

		if (pData != nullptr)
		{
			VulkanCheckResult(pBuffer->Map());
			memcpy(pBuffer->pMappedMemory, pData, bufferSize);
			
			if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0u)
			{
				pBuffer->Flush();
			}

			pBuffer->Unmap();
		}

		pBuffer->SetupDescriptor();

		return pBuffer->Bind();
	}

	void VulkanDevice::CopyBuffer(VulkanBuffer* pSrc, VulkanBuffer* pDst, VkQueue pQueue, VkBufferCopy* pCopyRegion)
	{
		assert(pDst->size <= pSrc->size);
		assert(pSrc->pHandle);

		VkCommandBuffer pCopyCommandBuffer = CreateCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);
		VkBufferCopy bufferCopy = {};

		if (pCopyRegion == VK_NULL_HANDLE)
		{
			bufferCopy.size = pSrc->size;
		}
		else
		{
			bufferCopy = *pCopyRegion;
		}

		vkCmdCopyBuffer(pCopyCommandBuffer, pSrc->pHandle, pDst->pHandle, 1u, &bufferCopy);

		FlushCommandBuffer(pCopyCommandBuffer, pQueue);
	}

	VkCommandPool VulkanDevice::CreateCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags commandPoolCreateFlags)
	{
		VkCommandPoolCreateInfo commandPoolCreateInfo = {};
		commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
		commandPoolCreateInfo.flags = commandPoolCreateFlags;

		VkCommandPool pCommandPool;
		VulkanCheckResult(vkCreateCommandPool(pLogicalDevice, &commandPoolCreateInfo, nullptr, &pCommandPool));
		return pCommandPool;
	}

	VkCommandBuffer VulkanDevice::CreateCommandBuffer(VkCommandBufferLevel level, VkCommandPool pCommandPool, bool begin)
	{
		VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
		commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		commandBufferAllocateInfo.commandPool = pCommandPool;
		commandBufferAllocateInfo.level = level;
		commandBufferAllocateInfo.commandBufferCount = 1u;

		VkCommandBuffer pCommandBuffer;
		
		VulkanCheckResult(vkAllocateCommandBuffers(pLogicalDevice, &commandBufferAllocateInfo, &pCommandBuffer));

		if (begin)
		{
			VkCommandBufferBeginInfo commandBufferBeginInfo = {};
			commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

			VulkanCheckResult(vkBeginCommandBuffer(pCommandBuffer, &commandBufferBeginInfo));
		}

		return pCommandBuffer;
	}

	VkCommandBuffer VulkanDevice::CreateCommandBuffer(VkCommandBufferLevel level, bool begin)
	{
		return CreateCommandBuffer(level, pCommandPool, begin);
	}


	void VulkanDevice::FlushCommandBuffer(VkCommandBuffer pCommandBuffer, VkQueue pQueue, VkCommandPool pCommandPool, bool free)
	{
		if (pCommandBuffer == VK_NULL_HANDLE)
		{
			return;
		}

		VulkanCheckResult(vkEndCommandBuffer(pCommandBuffer));

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1u;
		submitInfo.pCommandBuffers = &pCommandBuffer;
		
		VkFenceCreateInfo fenceCreateInfo = {};
		fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceCreateInfo.flags = VK_FLAGS_NONE;
		
		VkFence pFence;
		
		VulkanCheckResult(vkCreateFence(pLogicalDevice, &fenceCreateInfo, nullptr, &pFence));
		VulkanCheckResult(vkQueueSubmit(pQueue, 1u, &submitInfo, pFence));
		VulkanCheckResult(vkWaitForFences(pLogicalDevice, 1u, &pFence, VK_TRUE, VK_DEFAULT_FENCE_TIMEOUT));
		
		vkDestroyFence(pLogicalDevice, pFence, nullptr);
		
		if (free)
		{
			vkFreeCommandBuffers(pLogicalDevice, pCommandPool, 1u, &pCommandBuffer);
		}
	}

	void VulkanDevice::FlushCommandBuffer(VkCommandBuffer pCommandBuffer, VkQueue pQueue, bool free)
	{
		return FlushCommandBuffer(pCommandBuffer, pQueue, pCommandPool, free);
	}

	bool VulkanDevice::IsExtensionSupported(std::string_view extension)
	{
		return Contains(supportedExtensions, extension);
	}
}

#endif