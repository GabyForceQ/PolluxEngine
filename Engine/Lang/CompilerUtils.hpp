/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	class CompilerUtils final
	{
	public:
		bool IsBoolean(std::string value) noexcept;

		bool IsInteger(std::string value) noexcept;

		bool IsString(std::string value) noexcept;

		std::string BoolToString(const bool& value) noexcept;

		std::string BoolToString(const int32_t& value) noexcept;

		bool StringToBoolean(const std::string& value) noexcept;

		void RemoveLastZerosFromFloat(std::string& value) noexcept;

		void RemoveParensIf(std::string& value) noexcept;

		std::string CombineStrings(const std::string& lhs, const std::string& rhs) noexcept;

		bool IsSubExpression(const std::string& value) noexcept;
	};
}