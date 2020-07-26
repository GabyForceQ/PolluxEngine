/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class BuildPlatform
	{
		Windows
	};

	extern const char* g_BuildPlatform_Windows;

	extern const std::map<const char*, BuildPlatform> g_BuildPlatformMap;

	BuildPlatform BuildPlatformToEnum(const char* buildPlatform);

	std::string ToString(const BuildPlatform buildPlatform);
}