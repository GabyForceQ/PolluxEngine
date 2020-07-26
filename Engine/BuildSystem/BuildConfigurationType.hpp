/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class BuildConfigurationType
	{
		Debug,
		Release,
		Retail
	};

	extern const char* g_BuildConfigurationType_Debug;
	extern const char* g_BuildConfigurationType_Release;
	extern const char* g_BuildConfigurationType_Retail;

	extern const std::map<const char*, BuildConfigurationType> g_BuildConfigurationTypeMap;

	BuildConfigurationType BuildConfigurationTypeToEnum(const char* buildConfigurationType);

	std::string ToString(const BuildConfigurationType buildConfigurationType);
}