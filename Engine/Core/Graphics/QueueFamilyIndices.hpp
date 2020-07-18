/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Core
{
	/*************************************************************************************************************************
	 * \struct Queue Family Indices
	 * \brief Encapsulates family indices of a graphics queue
	 *************************************************************************************************************************/
	struct QueueFamilyIndices
	{
		/*********************************************************************************************************************
		 * Graphics queue
		 *********************************************************************************************************************/
		uint32_t graphics;

		/*********************************************************************************************************************
		 * Compute queue
		 *********************************************************************************************************************/
		uint32_t compute;

		/*********************************************************************************************************************
		 * Transfer queue
		 *********************************************************************************************************************/
		uint32_t transfer;
	};
}