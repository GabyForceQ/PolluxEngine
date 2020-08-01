/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class BuildSubSystem
	{
		Console,
		Windows,
		Native
	};

	extern const size_t g_BuildSubSystemCount;

	extern const char* g_BuildSubSystem_Console;

	extern const char* g_BuildSubSystem_Windows;

	extern const char* g_BuildSubSystem_Native;

	extern const std::map<const char*, BuildSubSystem> g_BuildSubSystemMap;

	BuildSubSystem BuildSubSystemToEnum(const char* buildSubSystem);

	std::string ToString(const BuildSubSystem buildSubSystem);
}