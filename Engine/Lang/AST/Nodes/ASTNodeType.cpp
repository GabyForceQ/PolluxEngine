/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeType.hpp"

namespace Pollux::Lang
{
	ASTNodeType::ASTNodeType(Token token) noexcept
		:
		ASTNodeBase{ std::move(token) }
	{
		RegisterType("ASTNodeType", +ASTNodeKind::ASTNodeType);
	}

	void ASTNodeType::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}