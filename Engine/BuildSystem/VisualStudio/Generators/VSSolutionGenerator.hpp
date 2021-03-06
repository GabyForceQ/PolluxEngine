/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../Interfaces/ISolutionGenerator.hpp"

namespace Pollux::BuildSystem
{
	class VSSolutionGenerator final : public ISolutionGenerator
	{
	public:
		std::string Generate(Solution* pSolution) override;
	};
}