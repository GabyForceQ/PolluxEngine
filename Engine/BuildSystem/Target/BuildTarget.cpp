/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildTarget.hpp"

namespace Pollux::BuildSystem
{
	BuildTarget::BuildTarget(BuildOptimization optimization, BuildPlatform platform, DevelopmentEnvironment developmentEnvironment) noexcept
		:
		optimization{ std::move(optimization) },
		platform{ std::move(platform) },
		developmentEnvironment{ std::move(developmentEnvironment) }
	{
	}
}