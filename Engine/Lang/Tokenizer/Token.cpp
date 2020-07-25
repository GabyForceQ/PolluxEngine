/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Token.hpp"

namespace Pollux::Lang
{
	Token::Token(TokenKind tokenKind, std::string_view value) noexcept
		:
		kind{ std::move(kind) },
		value{ std::move(value) }
	{
	}

	std::string Token::ToString() const
	{
		return "Token({ " + Lang::ToString(kind) + " }, { " + value + " })\n";
	}
}