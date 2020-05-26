/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "UTF8ParseError.hpp"

namespace Pollux
{
	UTF8ParseError::UTF8ParseError(const char* message)
		:
		std::logic_error{ message }
	{
	}
}