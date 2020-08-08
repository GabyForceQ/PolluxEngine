/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "DevelopmentEnvironment.hpp"
#include "BuildOptimization.hpp"
#include "BuildPlatform.hpp"

namespace Pollux::BuildSystem
{
	struct BuildTarget final
	{
	public:
		BuildTarget() noexcept = default;

		explicit BuildTarget(BuildOptimization optimization,
			BuildPlatform platform,
			DevelopmentEnvironment developmentEnvironment) noexcept;

		BuildOptimization optimization = BuildOptimization::None;

		BuildOptimization currentOptimization = BuildOptimization::None;

		BuildPlatform platform = BuildPlatform::Windows;

		DevelopmentEnvironment developmentEnvironment = DevelopmentEnvironment::Makefile;
	};
}