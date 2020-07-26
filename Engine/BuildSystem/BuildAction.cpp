/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildAction.hpp"

namespace Pollux::BuildSystem
{
	const char* g_BuildAction_None = "BuildAction::None";
	const char* g_BuildAction_GenerateProject = "BuildAction::GenerateProject";

	const std::map<const char*, BuildAction> g_BuildActionmMap
	{
		{ g_BuildAction_None, BuildAction::None },
		{ g_BuildAction_GenerateProject, BuildAction::GenerateProject }
	};

	BuildAction BuildActionToEnum(const char* buildAction)
	{
		if (g_BuildActionmMap.contains(buildAction))
		{
			return g_BuildActionmMap.at(buildAction);
		}

		throw std::runtime_error("Error (BuildSystem): BuildAction string is not valid.");
	}

	std::string ToString(const BuildAction buildAction)
	{
		switch (buildAction)
		{
		case BuildAction::None: return g_BuildAction_None;
		case BuildAction::GenerateProject: return g_BuildAction_GenerateProject;
		default:; // todo. Log a warning message
		}

		return g_pEmptyString;
	}
}