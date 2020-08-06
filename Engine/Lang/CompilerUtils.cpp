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

	std::string CompilerUtils::BoolToString(const bool& value) noexcept
	{
		return value ? "true" : "false";
	}

	std::string CompilerUtils::BoolToString(const int32_t& value) noexcept
	{
		return value != 0 ? "true" : "false";
	}

	bool CompilerUtils::StringToBoolean(const std::string& value) noexcept
	{
		return value == "true";
	}

	void CompilerUtils::RemoveLastZerosFromFloat(std::string& value) noexcept
	{
		for (size_t i = value.length() - 1, j = 0; i >= 0; i--, j++)
		{
			if (value[i] != '0')
			{
				value = value.substr(0, value.length() - j);
				break;
			}
		}
	}

	void CompilerUtils::RemoveParensIf(std::string& value) noexcept
	{
		if (value[0] == '(' && value[value.length() - 1] == ')')
		{
			value = value.substr(1, value.length() - 2);
		}
	}

	std::string CompilerUtils::CombineStrings(const std::string& lhs, const std::string& rhs) noexcept
	{
		return lhs.substr(0, lhs.length() - 1) + rhs.substr(1, rhs.length() - 1);
	}

	bool CompilerUtils::IsSubExpression(const std::string& value) noexcept
	{
		return value[0] == '(' && value[value.size() - 1] == ')';
	}
}