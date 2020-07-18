/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "GenericUtils.hpp"

namespace Pollux::Core
{
	bool Contains(const std::vector<std::string>& vec, std::string_view val) noexcept
	{
		return std::find(vec.begin(), vec.end(), val) != vec.end();
	}
}