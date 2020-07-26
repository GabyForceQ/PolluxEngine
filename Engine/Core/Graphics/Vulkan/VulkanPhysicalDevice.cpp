/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#ifdef POLLUX_DRIVER_VULKAN

#include "VulkanPhysicalDevice.hpp"

namespace Pollux::Core
{
	void VulkanPhysicalDevice::FillFeaturesAndProperties()
	{
		vkGetPhysicalDeviceProperties(pHandle, &properties);
		vkGetPhysicalDeviceFeatures(pHandle, &features);
		vkGetPhysicalDeviceMemoryProperties(pHandle, &memoryProperties);
	}
}

#endif