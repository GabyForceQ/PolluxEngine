/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../Interfaces/IBuildConfiguration.hpp"
#include "../Configuration/BuildConfiguration.hpp"
#include "../Configuration/BuildSubSystem.hpp"

namespace Pollux::BuildSystem
{
	struct VSProjectFilters;
	class VSProjectFiltersGenerator;
	class Solution;
	class Project;

	class ProjectFilters final
	{
	public:
		ProjectFilters(Project* pProject) noexcept;

		const std::string& GetPath() const noexcept;
		
		const std::vector<std::string>& GetHeaderFiles() const noexcept;
		
		const std::vector<std::string>& GetSourceFiles() const noexcept;
		
		const std::set<std::string>& GetFilters() const noexcept;

		const std::string& GetGeneratedCode() const noexcept;

		VSProjectFilters* pVSProjectFilters = nullptr; ///////

		Project* pProject = nullptr; ///////

		std::string path; ////////

	private:
		std::vector<std::string> headerFiles;
		std::vector<std::string> sourceFiles;
		std::set<std::string> filters;
		std::string generatedCode;

		friend VSProjectFiltersGenerator;
		friend Solution;
	};
}