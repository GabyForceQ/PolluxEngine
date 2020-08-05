/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	class ProjectFilters;

	class IProjectFiltersGenerator
	{
	public:
		virtual void Generate(ProjectFilters* pProjectFilters) = 0;

	protected:
		virtual std::string GetFilterBasePath(const std::string& fullPath, const std::string& projectName) = 0;
	};
}