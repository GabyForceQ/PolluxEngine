/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#ifdef POLLUX_DRIVER_VULKAN

#include "VulkanPhysicalDevice.hpp"
#include "../QueueFamilyIndices.hpp"

namespace Pollux::Core
{
	class VulkanBuffer;

	/*************************************************************************************************************************
	 * \class Vulkan Device
	 *************************************************************************************************************************/
	class VulkanDevice final
	{
	public:
		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VulkanDevice(VkPhysicalDevice pPhysicalDevice);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		~VulkanDevice();

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		uint32_t GetMemoryType(uint32_t typeBits, VkMemoryPropertyFlags memoryPropertyFlags,
			VkBool32* pMemoryTypeFound = nullptr);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		uint32_t GetQueueFamilyIndex(VkQueueFlagBits queueFlagBits);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkFormat GetSupportedDepthFormat(bool bCheckSamplingSupport);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkResult CreateLogicalDevice(VkPhysicalDeviceFeatures enabledFeatures,
			std::vector<const char*> pEnabledExtensions, void* pNextChain, bool bUseSwapChain = true,
			VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkResult CreateBuffer(VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags memoryPropertyFlags,
			VkDeviceSize bufferSize, VkBuffer* pBuffer, VkDeviceMemory* pDeviceMemory, void* pData = nullptr);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkResult CreateBuffer(VkBufferUsageFlags bufferUsageFlags, VkMemoryPropertyFlags memoryPropertyFlags,
			VulkanBuffer* pBuffer, VkDeviceSize bufferSize, void* pData = nullptr);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		void CopyBuffer(VulkanBuffer* pSrc, VulkanBuffer* pDst, VkQueue pQueue, VkBufferCopy* pCopyRegion = nullptr);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkCommandPool CreateCommandPool(uint32_t queueFamilyIndex,
			VkCommandPoolCreateFlags commandPoolCreateFlags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkCommandBuffer CreateCommandBuffer(VkCommandBufferLevel level, VkCommandPool pCommandPool, bool begin = false);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkCommandBuffer CreateCommandBuffer(VkCommandBufferLevel level, bool begin = false);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		void FlushCommandBuffer(VkCommandBuffer pCommandBuffer, VkQueue pQueue, VkCommandPool pCommandPool, bool free = true);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		void FlushCommandBuffer(VkCommandBuffer pCommandBuffer, VkQueue pQueue, bool free = true);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		bool IsExtensionSupported(std::string_view extension);

		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VulkanPhysicalDevice physicalDevice;
		
		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkDevice pLogicalDevice = VK_NULL_HANDLE;
		
		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		QueueFamilyIndices queueFamilyIndices;
		
		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		std::vector<VkQueueFamilyProperties> queueFamilyProperties;
		
		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		std::vector<std::string> supportedExtensions;
		
		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		VkCommandPool pCommandPool = VK_NULL_HANDLE;
		
		/*********************************************************************************************************************
		 *
		 *********************************************************************************************************************/
		bool bEnableDebugMarkers = false;
	};
}

#endif