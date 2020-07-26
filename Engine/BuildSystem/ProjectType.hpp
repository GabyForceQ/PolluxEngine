/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class ProjectType
	{
		VS2019
	};

	extern const char* g_ProjectType_VS2019;

	extern const std::map<const char*, ProjectType> g_ProjectTypeMap;

	ProjectType ProjectTypeToEnum(const char* projectType);

	std::string ToString(const ProjectType projectType);
}