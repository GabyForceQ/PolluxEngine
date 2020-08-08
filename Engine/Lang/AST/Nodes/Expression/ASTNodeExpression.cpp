/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeExpression.hpp"

namespace Pollux::Lang
{
	ASTNodeExpression::ASTNodeExpression(ExpressionKind kind) noexcept
		:
		ASTNodeBase{ Token{ TokenKind::Undefined, g_pEmptyString } },
		kind{ std::move(kind) }
	{
		RegisterType("ASTNodeExpression", +ASTNodeKind::ASTNodeExpression);
	}

	void ASTNodeExpression::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}