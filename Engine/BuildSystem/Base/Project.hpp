/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../BuildConfiguration.hpp"

namespace Pollux::BuildSystem
{
	class Project
	{
	public:
		const std::string name;

		const std::string path;

		const std::vector<BuildConfiguration> configurations;

		const std::vector<std::string> preprocessorDefinitions;
	};
}