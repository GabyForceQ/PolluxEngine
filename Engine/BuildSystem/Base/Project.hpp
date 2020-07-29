/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../Interfaces/IBuildConfiguration.hpp"
#include "../Interfaces/IProjectConfiguration.hpp"
#include "../BuildConfiguration.hpp"

namespace Pollux::BuildSystem
{
	class VSProject;
	class VSProjectGenerator;
	class VSSolution;
	class VSSolutionGenerator;
	class Solution;

	class Project : protected IBuildConfiguration, private IProjectConfiguration
	{
	public:
		const std::string& GetName() const noexcept;
		
		const std::string& GetPath() const noexcept;

		const std::string& GetPrecompiledHeaderName() const noexcept;

		bool UsePrecompiledHeaders() const noexcept;

	protected:
		std::string name;

		std::string path;

		std::vector<BuildConfiguration> configurations;

		std::vector<std::string> preprocessorDefinitions;

		std::string precompiledHeaderName;

		bool bUsePrecompiledHeaders = true;

	private:
		void SetProjectType(ProjectType projectType) override;

		VSProject* pVSProject = nullptr;
		VSProjectGenerator* pVSProjectGenerator = nullptr;

		friend VSProject;
		friend VSProjectGenerator;
		friend VSSolution;
		friend VSSolutionGenerator;
		friend Solution;
	};
}