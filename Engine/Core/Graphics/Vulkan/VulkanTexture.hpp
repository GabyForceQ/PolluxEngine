/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#ifdef POLLUX_DRIVER_VULKAN

namespace Pollux::Core
{
	class VulkanDevice;

	class Texture
	{
	public:
		VulkanDevice* m_pDevice;
		VkImage m_pImage;
		VkImageLayout m_ImageLayout;
		VkDeviceMemory m_pDeviceMemory;
		VkImageView m_pView;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_MipLevels;
		uint32_t m_LayerCount;
		VkDescriptorImageInfo m_Descriptor;
		VkSampler m_Sampler;

		void UpdateDescriptor();

		void Destroy();

		ktxResult LoadKTXFile(const std::string& fileName, ktxTexture** target);
	};

	class Texture2D : public Texture
	{
	public:
		void LoadFromFile(const std::string& fileName, VkFormat format, VulkanDevice* pDevice,
			VkQueue pCopyQueue, VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_SAMPLED_BIT,
			VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, bool bForceLinear = false);

		void LoadFromBuffer(void* pBuffer, VkDeviceSize pBufferSize, VkFormat pFormat,
			uint32_t pTextureWidth, uint32_t pTextureHeight, VulkanDevice* pDevice, VkQueue pCopyQueue,
			VkFilter filter = VK_FILTER_LINEAR, VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_SAMPLED_BIT,
			VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	};

	class Texture2DArray : public Texture
	{
	public:
		void LoadFromFile(
			const std::string& fileName, VkFormat format, VulkanDevice* pDevice,
			VkQueue pCopyQueue, VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_SAMPLED_BIT,
			VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	};

	class TextureCubeMap : public Texture
	{
	public:
		void LoadFromFile(
			const std::string& fileName, VkFormat format, VulkanDevice* pDevice,
			VkQueue pCopyQueue, VkImageUsageFlags imageUsageFlags = VK_IMAGE_USAGE_SAMPLED_BIT,
			VkImageLayout imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	};
}

#endif