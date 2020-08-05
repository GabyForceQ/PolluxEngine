/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../Interfaces/IProjectFilterGenerator.hpp"

namespace Pollux::BuildSystem
{
	class VSProjectFiltersGenerator final : public IProjectFiltersGenerator
	{
	public:
		void Generate(ProjectFilters* pProjectFilters) override;

	private:
		std::string GetFilterBasePath(const std::string& fullPath, const std::string& projectName) override;
	};
}