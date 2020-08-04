/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeScope.hpp"

namespace Pollux::Lang
{
	ASTNodeScope::ASTNodeScope(Token token) noexcept
		:
		ASTNodeBase{ std::move(token) }
	{
		ASTNodeBase::RegisterType("ASTNodeScope", +ASTNodeKind::ASTNodeScope);
	}

	void ASTNodeScope::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}