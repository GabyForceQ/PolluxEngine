/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildSystem.hpp"

namespace Pollux::BuildSystem
{
	void BuildSystem::Reset()
	{
		globalConfiguration->Reset();
		
		for (const auto& configuration : configurationMap)
		{
			configuration.second->Reset();
		}
	}

	BuildSystem& BuildSystem::operator=(const BuildSystem& rhs)
	{
		target = rhs.target;
		globalConfiguration = new BuildConfiguration(rhs.globalConfiguration->optimization);
		*globalConfiguration = *rhs.globalConfiguration;
		
		for (const auto& configuration : rhs.configurationMap)
		{
			configurationMap[configuration.first] = new BuildConfiguration(configuration.second->optimization);
			*configurationMap[configuration.first] = *configuration.second;
		}

		return *this;
	}
}