/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "Tokenizer/Token.hpp"
#include "PxTypes.hpp"

namespace Pollux::Lang
{
	struct ParseContext final
	{
		const ParseContext* m_pOwner = nullptr;

		std::vector<Token> m_Tokens;
		
		size_t m_TokenCount = 0_sz;
		
		size_t m_CurrentTokenIndex = 0_sz;
				
		bool m_bConstant = false;
		
		bool m_bTokenSteal = false;
				
		PxScope m_Scope;
	};
}