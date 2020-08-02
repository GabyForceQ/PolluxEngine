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
	struct VSProject;
	class VSProjectGenerator;
	struct VSSolution;
	class VSSolutionGenerator;
	class Solution;
	class BuildSystem;

	class Project : protected IBuildConfiguration
	{
	public:
		Project() noexcept;

		void Initialize(BuildSystem* pBuildSystem); ///////

		const std::string& GetName() const noexcept;
		
		const std::string& GetPath() const noexcept;

		VSProject* pVSProject = nullptr; ///////

		const std::string& GetGeneratedCode() const noexcept;

		BuildSystem* pBuildSystem = nullptr; //////

	protected:
		void ConfigureWin64(BuildConfiguration& config, const BuildTarget& target) override;

		void ConfigureAll(BuildConfiguration& config, const BuildTarget& target) override;

		void PostConfig(BuildConfiguration& globalConfig, BuildConfiguration& config, const BuildTarget& target) override;

		std::string name;

		std::string path;

		BuildSubSystem buildSubSystem = BuildSubSystem::Console;

	private:
		VSProjectGenerator* pVSProjectGenerator = nullptr;
		std::string generatedCode;

		friend VSProject;
		friend VSProjectGenerator;
		friend VSSolution;
		friend VSSolutionGenerator;
		friend Solution;
	};
}