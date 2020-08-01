/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::EngineBuilder
{
	class PolluxEngineSolution final : public BuildSystem::Solution
	{
	public:
		PolluxEngineSolution(const std::string& path) noexcept;
	};
}