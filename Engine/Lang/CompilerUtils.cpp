/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "CompilerUtils.hpp"

namespace Pollux::Lang
{
	bool CompilerUtils::IsBoolean(std::string value) noexcept
	{
		return value == "true" || value == "false";
	}

	bool CompilerUtils::IsInteger(std::string value) noexcept
	{
		if (value[0] == '(' && value[value.length() - 1] == ')')
		{
			value = value.substr(1, value.length() - 2);
		}

		if (value[0] == '-' || value[0] == '+')
		{
			value = value.substr(1, value.length() - 1);
		}

		return !value.empty() && std::find_if(value.begin(), value.end(), [](char c)
		{
			return !std::isdigit(c);
		}) == value.end();
	}

	bool CompilerUtils::IsString(std::string value) noexcept
	{
		return value[0] == '"' && value[value.length() - 1] == '"';
	}
}