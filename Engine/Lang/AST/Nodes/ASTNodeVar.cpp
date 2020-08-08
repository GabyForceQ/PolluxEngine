/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeVar.hpp"

namespace Pollux::Lang
{
	ASTNodeVar::ASTNodeVar(Token token) noexcept
		:
		ASTNodeBase{ std::move(token) }
	{
		RegisterType("ASTNodeVar", +ASTNodeKind::ASTNodeVar);
	}

	void ASTNodeVar::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}