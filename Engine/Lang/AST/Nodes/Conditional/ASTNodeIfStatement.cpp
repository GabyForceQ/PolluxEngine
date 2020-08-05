/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeIfStatement.hpp"

namespace Pollux::Lang
{
	ASTNodeIfStatement::ASTNodeIfStatement() noexcept
		:
		ASTNodeBase{ Token{ TokenKind::Undefined, g_pEmptyString } }
	{
		RegisterType("ASTNodeIfStatement", +ASTNodeKind::ASTNodeIfStatement);
	}

	void ASTNodeIfStatement::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}