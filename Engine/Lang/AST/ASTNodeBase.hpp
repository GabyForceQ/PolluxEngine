/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "IASTNodeVisitor.hpp"
#include "ASTNodeKind.hpp"
#include "../Tokenizer/Token.hpp"
#include "../../Core/OOP/Type.hpp"

namespace Pollux::Lang
{
	class ASTNodeBase : public Core::Type
	{
	public:
		explicit ASTNodeBase(Token token) noexcept;

		virtual void Accept(IASTNodeVisitor* pVisitor) = 0;

		Token token;

		std::string content;
	};
}