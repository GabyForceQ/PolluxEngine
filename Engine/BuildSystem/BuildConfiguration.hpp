/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "BuildPlatform.hpp"
#include "BuildConfigurationType.hpp"

namespace Pollux::BuildSystem
{
	struct BuildConfiguration final
	{
		std::string name;
		
		BuildPlatform platform = BuildPlatform::Windows;
		
		const std::string architecture = "x64";

		BuildConfigurationType type = BuildConfigurationType::Debug;
	};
}