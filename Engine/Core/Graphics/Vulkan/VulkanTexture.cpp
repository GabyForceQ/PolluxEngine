/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#ifdef POLLUX_DRIVER_VULKAN

#include "VulkanTexture.hpp"
#include "VulkanBase.hpp"
#include "VulkanTools.hpp"
#include "VulkanDevice.hpp"

namespace Pollux::Core
{
	void Texture::UpdateDescriptor()
	{
		m_Descriptor.sampler = m_Sampler;
		m_Descriptor.imageView = m_pView;
		m_Descriptor.imageLayout = m_ImageLayout;
	}

	void Texture::Destroy()
	{
		vkDestroyImageView(m_pDevice->pLogicalDevice, m_pView, nullptr);
		vkDestroyImage(m_pDevice->pLogicalDevice, m_pImage, nullptr);

		if (m_Sampler)
		{
			vkDestroySampler(m_pDevice->pLogicalDevice, m_Sampler, nullptr);
		}

		vkFreeMemory(m_pDevice->pLogicalDevice, m_pDeviceMemory, nullptr);
	}

	ktxResult Texture::LoadKTXFile(const std::string& fileName, ktxTexture** target)
	{
		ktxResult res = KTX_SUCCESS;

		// todo. check if file exists

		res = ktxTexture_CreateFromNamedFile(fileName.c_str(), KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT, target);

		return res;
	}

	void Texture2D::LoadFromFile(const std::string& fileName, VkFormat format, VulkanDevice* pDevice,
		VkQueue pCopyQueue, VkImageUsageFlags imageUsageFlags, VkImageLayout imageLayout, bool bForceLinear)
	{
		ktxTexture* ktxTexture = nullptr;
		ktxResult result = LoadKTXFile(fileName, &ktxTexture);
		assert(result == KTX_SUCCESS);

		this->m_pDevice = pDevice;
		m_Width = ktxTexture->baseWidth;
		m_Height = ktxTexture->baseHeight;
		m_MipLevels = ktxTexture->numLevels;

		ktx_uint8_t* ktxTextureData = ktxTexture_GetData(ktxTexture);
		ktx_size_t ktxTextureSize = ktxTexture_GetSize(ktxTexture);

		VkFormatProperties formatProperties;
		vkGetPhysicalDeviceFormatProperties(pDevice->physicalDevice.pHandle, format, &formatProperties);

		VkBool32 useStaging = !bForceLinear;

		VkMemoryAllocateInfo memoryAllocateInfo = {};
		memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;

		VkMemoryRequirements memoryRequirements;

		VkCommandBuffer pCopyCommandBuffer = pDevice->CreateCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);

		if (useStaging)
		{
			VkBuffer pStagingBuffer;
			VkDeviceMemory pStagingMemory;

			VkBufferCreateInfo bufferCreateInfo = {};
			bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			bufferCreateInfo.size = ktxTextureSize;
			bufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
			bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

			VulkanCheckResult(vkCreateBuffer(pDevice->pLogicalDevice, &bufferCreateInfo, nullptr, &pStagingBuffer));

			vkGetBufferMemoryRequirements(pDevice->pLogicalDevice, pStagingBuffer, &memoryRequirements);

			memoryAllocateInfo.allocationSize = memoryRequirements.size;
			memoryAllocateInfo.memoryTypeIndex = pDevice->GetMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			VulkanCheckResult(vkAllocateMemory(pDevice->pLogicalDevice, &memoryAllocateInfo, nullptr, &pStagingMemory));
			VulkanCheckResult(vkBindBufferMemory(pDevice->pLogicalDevice, pStagingBuffer, pStagingMemory, 0));

			uint8_t* pData;
			VulkanCheckResult(vkMapMemory(pDevice->pLogicalDevice, pStagingMemory, 0, memoryRequirements.size, 0, (void**)&pData));
			memcpy(pData, ktxTextureData, ktxTextureSize);
			vkUnmapMemory(pDevice->pLogicalDevice, pStagingMemory);

			std::vector<VkBufferImageCopy> bufferCopyRegions;

			for (uint32_t i = 0u; i < m_MipLevels; i++)
			{
				ktx_size_t offset;
				KTX_error_code result = ktxTexture_GetImageOffset(ktxTexture, i, 0, 0, &offset);
				assert(result == KTX_SUCCESS);

				VkBufferImageCopy bufferCopyRegion = {};
				bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				bufferCopyRegion.imageSubresource.mipLevel = i;
				bufferCopyRegion.imageSubresource.baseArrayLayer = 0;
				bufferCopyRegion.imageSubresource.layerCount = 1;
				bufferCopyRegion.imageExtent.width = std::max(1u, ktxTexture->baseWidth >> i);
				bufferCopyRegion.imageExtent.height = std::max(1u, ktxTexture->baseHeight >> i);
				bufferCopyRegion.imageExtent.depth = 1;
				bufferCopyRegion.bufferOffset = offset;

				bufferCopyRegions.push_back(bufferCopyRegion);
			}

			VkImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
			imageCreateInfo.format = format;
			imageCreateInfo.mipLevels = m_MipLevels;
			imageCreateInfo.arrayLayers = 1;
			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
			imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			imageCreateInfo.extent = { m_Width, m_Height, 1 };
			imageCreateInfo.usage = imageUsageFlags;

			if (!(imageCreateInfo.usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT))
			{
				imageCreateInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
			}

			VulkanCheckResult(vkCreateImage(pDevice->pLogicalDevice, &imageCreateInfo, nullptr, &m_pImage));

			vkGetImageMemoryRequirements(pDevice->pLogicalDevice, m_pImage, &memoryRequirements);

			memoryAllocateInfo.allocationSize = memoryRequirements.size;
			memoryAllocateInfo.memoryTypeIndex = pDevice->GetMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

			VulkanCheckResult(vkAllocateMemory(pDevice->pLogicalDevice, &memoryAllocateInfo, nullptr, &m_pDeviceMemory));
			VulkanCheckResult(vkBindImageMemory(pDevice->pLogicalDevice, m_pImage, m_pDeviceMemory, 0));

			VkImageSubresourceRange subresourceRange = {};
			subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subresourceRange.baseMipLevel = 0;
			subresourceRange.levelCount = m_MipLevels;
			subresourceRange.layerCount = 1;

			VulkanTools::SetImageLayout(
				pCopyCommandBuffer,
				m_pImage,
				VK_IMAGE_LAYOUT_UNDEFINED,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				subresourceRange);

			vkCmdCopyBufferToImage(
				pCopyCommandBuffer,
				pStagingBuffer,
				m_pImage,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				static_cast<uint32_t>(bufferCopyRegions.size()),
				bufferCopyRegions.data()
			);

			this->m_ImageLayout = imageLayout;

			VulkanTools::SetImageLayout(
				pCopyCommandBuffer,
				m_pImage,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				imageLayout,
				subresourceRange);

			m_pDevice->FlushCommandBuffer(pCopyCommandBuffer, pCopyQueue);

			vkFreeMemory(pDevice->pLogicalDevice, pStagingMemory, nullptr);
			vkDestroyBuffer(pDevice->pLogicalDevice, pStagingBuffer, nullptr);
		}
		else
		{
			assert(formatProperties.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT);

			VkImage mappableImage;
			VkDeviceMemory mappableMemory;

			VkImageCreateInfo imageCreateInfo = {};
			imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
			imageCreateInfo.format = format;
			imageCreateInfo.extent = { m_Width, m_Height, 1 };
			imageCreateInfo.mipLevels = 1;
			imageCreateInfo.arrayLayers = 1;
			imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
			imageCreateInfo.tiling = VK_IMAGE_TILING_LINEAR;
			imageCreateInfo.usage = imageUsageFlags;
			imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

			VulkanCheckResult(vkCreateImage(pDevice->pLogicalDevice, &imageCreateInfo, nullptr, &mappableImage));

			vkGetImageMemoryRequirements(pDevice->pLogicalDevice, mappableImage, &memoryRequirements);

			memoryAllocateInfo.allocationSize = memoryRequirements.size;
			memoryAllocateInfo.memoryTypeIndex = pDevice->GetMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			VulkanCheckResult(vkAllocateMemory(pDevice->pLogicalDevice, &memoryAllocateInfo, nullptr, &mappableMemory));
			VulkanCheckResult(vkBindImageMemory(pDevice->pLogicalDevice, mappableImage, mappableMemory, 0));

			VkImageSubresource subRes = {};
			subRes.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			subRes.mipLevel = 0;

			VkSubresourceLayout subResLayout;

			void* pData;
			vkGetImageSubresourceLayout(pDevice->pLogicalDevice, mappableImage, &subRes, &subResLayout);
			VulkanCheckResult(vkMapMemory(pDevice->pLogicalDevice, mappableMemory, 0, memoryRequirements.size, 0, &pData));
			memcpy(pData, ktxTextureData, memoryRequirements.size);
			vkUnmapMemory(pDevice->pLogicalDevice, mappableMemory);

			m_pImage = mappableImage;
			m_pDeviceMemory = mappableMemory;
			m_ImageLayout = imageLayout;

			VulkanTools::SetImageLayout(pCopyCommandBuffer, m_pImage, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_UNDEFINED, imageLayout);

			pDevice->FlushCommandBuffer(pCopyCommandBuffer, pCopyQueue);
		}

		ktxTexture_Destroy(ktxTexture);

		VkSamplerCreateInfo samplerCreateInfo = {};
		samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
		samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
		samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerCreateInfo.mipLodBias = 0.0f;
		samplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
		samplerCreateInfo.minLod = 0.0f;
		samplerCreateInfo.maxLod = (useStaging) ? (float)m_MipLevels : 0.0f;
		samplerCreateInfo.maxAnisotropy = pDevice->physicalDevice.enabledFeatures.samplerAnisotropy ? pDevice->physicalDevice.properties.limits.maxSamplerAnisotropy : 1.0f;
		samplerCreateInfo.anisotropyEnable = pDevice->physicalDevice.enabledFeatures.samplerAnisotropy;
		samplerCreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
		VulkanCheckResult(vkCreateSampler(pDevice->pLogicalDevice, &samplerCreateInfo, nullptr, &m_Sampler));

		VkImageViewCreateInfo viewCreateInfo = {};
		viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewCreateInfo.format = format;
		viewCreateInfo.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
		viewCreateInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
		viewCreateInfo.subresourceRange.levelCount = (useStaging) ? m_MipLevels : 1;
		viewCreateInfo.image = m_pImage;

		VulkanCheckResult(vkCreateImageView(pDevice->pLogicalDevice, &viewCreateInfo, nullptr, &m_pView));

		UpdateDescriptor();
	}

	void Texture2D::LoadFromBuffer(void* pBuffer, VkDeviceSize pBufferSize, VkFormat pFormat,
		uint32_t pTextureWidth, uint32_t pTextureHeight, VulkanDevice* pDevice, VkQueue pCopyQueue,
		VkFilter filter, VkImageUsageFlags imageUsageFlags, VkImageLayout imageLayout)
	{
	}

	void Texture2DArray::LoadFromFile(const std::string& fileName, VkFormat format, VulkanDevice* pDevice,
		VkQueue pCopyQueue, VkImageUsageFlags imageUsageFlags, VkImageLayout imageLayout)
	{
	}

	void TextureCubeMap::LoadFromFile(const std::string& fileName, VkFormat format, VulkanDevice* pDevice,
		VkQueue pCopyQueue, VkImageUsageFlags imageUsageFlags, VkImageLayout imageLayout)
	{
	}
}

#endif