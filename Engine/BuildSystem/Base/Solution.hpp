/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../Interfaces/IBuildConfiguration.hpp"
#include "../Interfaces/IProjectConfiguration.hpp"

namespace Pollux::BuildSystem
{
	class VSSolution;
	class VSSolutionGenerator;
	class VSProject;
	class VSProjectGenerator;
	class Project;

	class Solution : protected IBuildConfiguration, private IProjectConfiguration
	{
	public:
		Solution(const std::vector<Project*>& pProjects);

		void SetProjectType(ProjectType projectType) override;

	protected:
		std::vector<Project*> pProjects;

	private:
		VSSolution* pVSSolution = nullptr;
		VSSolutionGenerator* pVSSolutionGenerator = nullptr;

		friend VSSolution;
		friend VSSolutionGenerator;
		friend VSProject;
		friend VSProjectGenerator;
	};
}