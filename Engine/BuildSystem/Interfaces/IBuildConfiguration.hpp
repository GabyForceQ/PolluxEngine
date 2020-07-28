/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../ProjectType.hpp"

namespace Pollux::BuildSystem
{
	class IBuildConfiguration
	{
	protected:
		virtual void SetProjectType(ProjectType projectType) = 0;
		virtual void ConfigureWin64() = 0;
	};
}