/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildTarget.hpp"

namespace Pollux::BuildSystem
{
	BuildTarget::BuildTarget(BuildPlatform platform, const std::string& name)
		:
		platform{ platform },
		name{ name }
	{
	}
}