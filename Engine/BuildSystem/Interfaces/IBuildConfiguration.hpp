/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../Target/BuildTarget.hpp"
#include "../Configuration/BuildConfiguration.hpp"

namespace Pollux::BuildSystem
{
	class IBuildConfiguration
	{
	protected:
		virtual void ConfigureWin64(BuildConfiguration& config, const BuildTarget& target) = 0;

		virtual void ConfigureAll(BuildConfiguration& config, const BuildTarget& target) = 0;

		virtual void PostConfig(BuildConfiguration& config, const BuildTarget& target) = 0;
	};
}