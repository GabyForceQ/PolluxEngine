/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildSubSystem.hpp"

namespace Pollux::BuildSystem
{
	const char* g_BuildSubSystem_Console = "BuildSubSystem::Console";
	const char* g_BuildSubSystem_Windows = "BuildSubSystem::Windows";
	const char* g_BuildSubSystem_Native = "BuildSubSystem::Native";

	const std::map<const char*, BuildSubSystem> g_BuildSubSystemMap
	{
		{ g_BuildSubSystem_Console, BuildSubSystem::Console },
		{ g_BuildSubSystem_Windows, BuildSubSystem::Windows },
		{ g_BuildSubSystem_Native, BuildSubSystem::Native }
	};

	BuildSubSystem BuildSubSystemToEnum(const char* buildSubSystem)
	{
		if (g_BuildSubSystemMap.contains(buildSubSystem))
		{
			return g_BuildSubSystemMap.at(buildSubSystem);
		}

		throw std::runtime_error("Error (BuildSystem): BuildSubSystem string is not valid.");
	}

	std::string ToString(const BuildSubSystem buildSubSystem)
	{
		switch (buildSubSystem)
		{
		case BuildSubSystem::Console: return g_BuildSubSystem_Console;
		case BuildSubSystem::Windows: return g_BuildSubSystem_Windows;
		case BuildSubSystem::Native: return g_BuildSubSystem_Native;
		}

		return g_pEmptyString;
	}
}