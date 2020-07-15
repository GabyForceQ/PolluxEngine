/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Test/testpch.hpp"

#ifdef POLLUX_DRIVER_VULKAN

#include "VulkanTests.hpp"
#include "Engine/Core/Graphics/Vulkan/VulkanBase.hpp"

namespace Pollux::Test
{
	UnitTestResult CreateDestroyVulkanInstance()
	{
		UnitTestResult res;
		static const char* pErrorMessageCreate = "VulkanInstance creation FAILED";
		static const char* pErrorMessageDestroy = "VulkanInstance destruction FAILED";
		bool initialized = false;

		try
		{
			// Create Vulkan Instance
			VkInstance instance = nullptr;
			std::vector<const char*> instanceLayers;
			std::vector<const char*> instanceExtensions;
			VkDebugReportCallbackCreateInfoEXT debugCallbackCreateInfo = {};

			VkApplicationInfo applicationInfo{};
			applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			applicationInfo.apiVersion = VK_MAKE_VERSION(1, 2, 141);
			applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
			applicationInfo.pApplicationName = "Pollux Engine Test";

			VkInstanceCreateInfo instanceCreateInfo = {};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &applicationInfo;
			instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(instanceLayers.size());
			instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();
			instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size());
			instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
			instanceCreateInfo.pNext = &debugCallbackCreateInfo;

			Core::VulkanCheckResult(vkCreateInstance(&instanceCreateInfo, nullptr, &instance));

			initialized = true;

			// Destroy Vulkan Instance
			vkDestroyInstance(instance, nullptr);
			instance = nullptr;
		}
		catch (...)
		{
			res.succeeded = false;
			res.message = initialized ? pErrorMessageDestroy : pErrorMessageCreate;
		}

		return std::move(res);
	}
}

#endif