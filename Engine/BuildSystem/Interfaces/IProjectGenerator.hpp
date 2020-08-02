/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../Target/BuildOptimization.hpp"
#include "../Configuration/BuildBooleanType.hpp"

namespace Pollux::BuildSystem
{
	class Project;
	class BuildSystem;

	class IProjectGenerator
	{
	public:
		virtual void Generate(Project* pProject) = 0;

	protected:
		virtual std::string GetBuildOptimization(const BuildOptimization optimization) = 0;
		virtual std::string GetBuildBooleanType(const BuildBooleanType booleanType) = 0;
		
		virtual std::string BoolToString(const bool value) = 0;
	};
}