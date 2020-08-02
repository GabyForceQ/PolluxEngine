/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../Interfaces/IProjectGenerator.hpp"

namespace Pollux::BuildSystem
{
	class VSProjectGenerator final : public IProjectGenerator
	{
	public:
		void Generate(Project* pProject) override;

	private:
		void GenerateSourceDirectory(Project* pProject);
		void GeneratePrecompiledHeader(Project* pProject, const std::string& precompiledHeaderName);
		
		std::string GetBuildOptimization(const BuildOptimization optimization) override;
		std::string GetBuildBooleanType(const BuildBooleanType booleanType) override;
		std::string BoolToString(const bool value) override;
	};
}