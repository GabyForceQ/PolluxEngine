/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#ifdef POLLUX_DRIVER_VULKAN

namespace Pollux::Test
{
	/**************************************************************************************************************************
	 * \brief Check if Vulkan API can be initialized and deinitialized through its instance.
	 * \return Test Result
	 *************************************************************************************************************************/
	UnitTestResult CreateDestroyVulkanInstance();
}

#endif