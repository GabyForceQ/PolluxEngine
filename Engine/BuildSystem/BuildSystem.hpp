/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "Target/BuildTarget.hpp"
#include "Configuration/BuildConfiguration.hpp"

namespace Pollux::BuildSystem
{
	class BuildSystem final
	{
	public:
		BuildSystem& operator=(const BuildSystem& rhs);

		void Reset();

		BuildTarget target;

		std::unordered_map<BuildOptimization, BuildConfiguration*> configurationMap;
	};
}