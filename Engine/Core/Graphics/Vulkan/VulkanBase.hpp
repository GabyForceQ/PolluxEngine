/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#ifdef POLLUX_DRIVER_VULKAN

#define VK_FLAGS_NONE 0
#define VK_DEFAULT_FENCE_TIMEOUT 100000000000

namespace Pollux::Core
{
	template <typename F>
	void VulkanCheckResult(F f)
	{
		if (VkResult res = (f); res != VK_SUCCESS)
		{
			// todo. log
			if (res != VK_SUCCESS)
			{
				throw std::runtime_error("Vulkan Error!");
			}
		}
	}
}

#endif