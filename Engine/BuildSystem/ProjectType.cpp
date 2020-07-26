/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ProjectType.hpp"

namespace Pollux::BuildSystem
{
	const char* g_ProjectType_VisualStudio = "ProjectType::VisualStudio";

	const std::map<const char*, ProjectType> g_ProjectTypeMap
	{
		{ g_ProjectType_VisualStudio, ProjectType::VisualStudio },
	};

	ProjectType ProjectTypeToEnum(const char* projectType)
	{
		if (g_ProjectTypeMap.contains(projectType))
		{
			return g_ProjectTypeMap.at(projectType);
		}

		throw std::runtime_error("Error (BuildSystem): ProjectType string is not valid.");
	}

	std::string ToString(const ProjectType projectType)
	{
		switch (projectType)
		{
		case ProjectType::VisualStudio: return g_ProjectType_VisualStudio;
		default:; // todo. Log a warning message
		}

		return g_pEmptyString;
	}
}