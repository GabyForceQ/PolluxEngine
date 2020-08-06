/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeDeclStatement.hpp"

namespace Pollux::Lang
{
	ASTNodeDeclStatement::ASTNodeDeclStatement() noexcept
		:
		ASTNodeBase{ Token{ TokenKind::Undefined, g_pEmptyString } }
	{
		RegisterType("ASTNodeDeclStatement", +ASTNodeKind::ASTNodeDeclStatement);
	}

	void ASTNodeDeclStatement::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}