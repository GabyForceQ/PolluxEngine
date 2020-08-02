/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildSystem.hpp"

namespace Pollux::BuildSystem
{
	void BuildSystem::Run()
	{
	}

	BuildSystem& BuildSystem::operator=(const BuildSystem& rhs)
	{
		target = rhs.target;
		globalConfiguration = new BuildConfiguration(rhs.globalConfiguration->optimization);
		*globalConfiguration = *rhs.globalConfiguration;
		
		for (const auto& e : rhs.configurationMap)
		{
			configurationMap[e.first] = new BuildConfiguration(e.second->optimization);
			*configurationMap[e.first] = *e.second;
		}

		return *this;
	}
}