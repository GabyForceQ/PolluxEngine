/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#ifdef POLLUX_DRIVER_VULKAN

namespace Pollux::Core
{
	class VulkanTools final
	{
	public:
		static std::string ErrorToString(VkResult errorCode);

		static std::string PhysicalDeviceTypeString(VkPhysicalDeviceType type);

		static VkBool32 GetSupportedDepthFormat(VkPhysicalDevice pPhysicalDevice, VkFormat* pDepthFormat);

		static VkBool32 FormatIsFilterable(VkPhysicalDevice pPhysicalDevice, VkFormat format, VkImageTiling tiling);

		static void SetImageLayout(
			VkCommandBuffer pCommandBuffer,
			VkImage pImage,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkImageSubresourceRange subresourceRange,
			VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
			VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

		static void SetImageLayout(
			VkCommandBuffer pCommandBuffer,
			VkImage pImage,
			VkImageAspectFlags aspectMask,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
			VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

		static void InsertImageMemoryBarrier(
			VkCommandBuffer pCommandBuffer,
			VkImage pImage,
			VkAccessFlags srcAccessMask,
			VkAccessFlags dstAccessMask,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkPipelineStageFlags srcStageMask,
			VkPipelineStageFlags dstStageMask,
			VkImageSubresourceRange subresourceRange);

		static VkShaderModule LoadShader(const char* fileName, VkDevice pDevice);
	};
}

#endif