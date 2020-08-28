/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Token.hpp"

namespace Pollux::Lang
{
	Token::Token(TokenKind kind, std::string_view value) noexcept
		:
		kind{ std::move(kind) },
		value{ std::move(value) }
	{
	}

	Token::Token(const Token& other) noexcept
		:
		kind{ other.kind },
		value{ other.value }
	{
	}

	Token::Token(Token&& other) noexcept
		:
		kind{ std::move(other.kind) },
		value{ std::move(other.value) }
	{
	}

	Token& Token::operator=(const Token& rhs) noexcept
	{
		kind = rhs.kind;
		value = rhs.value;

		return *this;
	}

	Token Token::Empty()
	{
		static Token token{ TokenKind::Undefined, g_pEmptyString };
		return token;
	}

	std::string Token::ToString() const
	{
		return "Token({ " + Lang::ToString(kind) + " }, { " + value + " })\n";
	}

	bool Token::IsKeyword() const noexcept
	{
		return g_TokenKindKeywordMap.contains(value.c_str());
	}
}