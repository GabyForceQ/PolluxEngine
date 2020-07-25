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
		TokenKind kind = TokenKind::Undefined;
		std::string value;

		explicit Token(TokenKind tokenKind, std::string_view value) noexcept;

		std::string ToString() const;
	};
}