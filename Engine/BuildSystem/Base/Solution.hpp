/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../Interfaces/IBuildConfiguration.hpp"

namespace Pollux::BuildSystem
{
	struct VSSolution;
	class VSSolutionGenerator;
	struct VSProject;
	class VSProjectGenerator;
	class Project;
	class BuildSystem;

	class Solution : protected IBuildConfiguration
	{
	public:
		Solution(const std::string& path) noexcept;

		void Implement(BuildSystem* pBuildSystem);

		const std::string& GetPath() const noexcept;

		std::vector<Project*> pProjects;

	protected:
		void ConfigureWin64(BuildConfiguration& config, const BuildTarget& target) override;

		void ConfigureAll(BuildConfiguration& config, const BuildTarget& target) override;

		void PostConfig(BuildConfiguration& globalConfig, BuildConfiguration& config, const BuildTarget& target) override;
		
	private:
		const std::string path;
		VSSolution* pVSSolution = nullptr;
		VSSolutionGenerator* pVSSolutionGenerator = nullptr;

		friend VSSolution;
		friend VSSolutionGenerator;
		friend VSProject;
		friend VSProjectGenerator;
	};
}