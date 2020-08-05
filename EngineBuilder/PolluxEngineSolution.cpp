/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "EngineBuilder/enginebuilderpch.hpp"

#include "PolluxEngineSolution.hpp"
#include "EngineProject.hpp"
#include "EditorProject.hpp"
#include "EngineBuilderProject.hpp"

namespace Pollux::EngineBuilder
{
	PolluxEngineSolution::PolluxEngineSolution(const std::string& path) noexcept
		:
		Solution{ path }
	{
		pProjects.push_back(new EngineProject());
		pProjects.push_back(new EditorProject());
		pProjects.push_back(new EngineBuilderProject());
	}
}