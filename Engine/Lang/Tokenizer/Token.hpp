/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "TokenKind.hpp"

namespace Pollux::Lang
{
	struct Token final
	{
		explicit Token(TokenKind kind, std::string_view value) noexcept;

		Token(const Token& other) noexcept;

		Token(Token&& other) noexcept;

		Token& operator=(const Token& rhs) noexcept;

		static Token Empty();

		std::string ToString() const;

		bool IsKeyword() const noexcept;

		TokenKind kind = TokenKind::Undefined;

		std::string value;
	};
}