/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../Base/Project.hpp"
#include "../VSGuid.hpp"

namespace Pollux::BuildSystem
{
	class VSProject final : public Project
	{
	public:
		const VSGuid guid = VSGuid::Create();
		
		const VSGuid type;

		const std::vector<VSGuid> dependencies;
	};
}