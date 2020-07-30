/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildPlatform.hpp"

namespace Pollux::BuildSystem
{
	const char* g_BuildPlatform_Windows = "BuildPlatform::Windows";

	const std::map<const char*, BuildPlatform> g_BuildPlatformMap
	{
		{ g_BuildPlatform_Windows, BuildPlatform::Windows },
	};

	BuildPlatform BuildPlatformToEnum(const char* buildPlatform)
	{
		if (g_BuildPlatformMap.contains(buildPlatform))
		{
			return g_BuildPlatformMap.at(buildPlatform);
		}

		throw std::runtime_error("Error (BuildSystem): BuildPlatform string is not valid.");
	}

	std::string ToString(const BuildPlatform buildPlatform)
	{
		switch (buildPlatform)
		{
		case BuildPlatform::Windows: return g_BuildPlatform_Windows;
		default:; // todo. Log a warning message
		}

		return g_pEmptyString;
	}
}