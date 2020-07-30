/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildPlatform.hpp"
#include "BuildConfigurationType.hpp"

namespace Pollux::BuildSystem
{
	const char* g_BuildConfigurationType_Debug = "BuildConfigurationType::Debug";
	const char* g_BuildConfigurationType_Release = "BuildConfigurationType::Release";
	const char* g_BuildConfigurationType_Retail = "BuildConfigurationType::Retail";

	const std::map<const char*, BuildConfigurationType> g_BuildConfigurationTypeMap
	{
		{ g_BuildConfigurationType_Debug, BuildConfigurationType::Debug },
		{ g_BuildConfigurationType_Release, BuildConfigurationType::Release },
		{ g_BuildConfigurationType_Retail, BuildConfigurationType::Retail }
	};

	BuildConfigurationType BuildConfigurationTypeToEnum(const char* buildConfigurationType)
	{
		if (g_BuildConfigurationTypeMap.contains(buildConfigurationType))
		{
			return g_BuildConfigurationTypeMap.at(buildConfigurationType);
		}

		throw std::runtime_error("Error (BuildSystem): BuildPlatform string is not valid.");
	}

	std::string ToString(const BuildConfigurationType buildConfigurationType)
	{
		switch (buildConfigurationType)
		{
		case BuildConfigurationType::Debug: return g_BuildConfigurationType_Debug;
		case BuildConfigurationType::Release: return g_BuildConfigurationType_Release;
		case BuildConfigurationType::Retail: return g_BuildConfigurationType_Retail;
		default:; // todo. Log a warning message
		}

		return g_pEmptyString;
	}
}