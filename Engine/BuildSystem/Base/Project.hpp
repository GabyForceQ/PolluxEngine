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
		std::string name;

		std::string path;

		std::vector<BuildConfiguration> configurations;

		std::vector<std::string> preprocessorDefinitions;
	};
}