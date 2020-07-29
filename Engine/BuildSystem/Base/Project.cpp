/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Project.hpp"
#include "Engine/BuildSystem/VisualStudio/Objects/VSProject.hpp"

namespace Pollux::BuildSystem
{
	const std::string& Project::GetName() const noexcept
	{
		return name;
	}

	const std::string& Project::GetPath() const noexcept
	{
		return path;
	}

	const std::string& Project::GetPrecompiledHeaderName() const noexcept
	{
		return precompiledHeaderName;
	}

	bool Project::UsePrecompiledHeaders() const noexcept
	{
		return bUsePrecompiledHeaders;
	}

    void Project::SetProjectType(ProjectType projectType)
    {
		this->projectType = projectType;

		switch (projectType)
		{
		case ProjectType::VS2019:
		{
			pVSProject = new VSProject();
		}
		}

		if (bUsePrecompiledHeaders)
		{
			precompiledHeaderName = name + "PCH";
		}
    }
}