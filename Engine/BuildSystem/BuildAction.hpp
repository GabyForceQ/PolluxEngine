/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class BuildAction
	{
		None,
		GenerateProject
	};

	extern const char* g_BuildAction_None;
	extern const char* g_BuildAction_GenerateProject;

	extern const std::map<const char*, BuildAction> g_BuildActionMap;

	BuildAction BuildActionToEnum(const char* buildAction);

	std::string ToString(const BuildAction buildAction);
}