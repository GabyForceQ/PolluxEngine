/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "Token.hpp"

namespace Pollux::Lang
{
	class Lexer final
	{
	public:
		explicit Lexer(std::string text) noexcept;

		void Advance();
		
		void SkipComment(const bool multiline);
		
		void SkipWhitespace();
		
		Token NumberLiteral();
		
		Token StringLiteral();
		
		/*********************************************************************************************************************
		 * Handle identifiers and reserved keywords
		 *********************************************************************************************************************/
		Token Identifier();
		
		Token NextToken();
		
		char Peek();

	private:
		std::string text;
		uint64_t position = 0ull;
		char currentChar;
	};
}