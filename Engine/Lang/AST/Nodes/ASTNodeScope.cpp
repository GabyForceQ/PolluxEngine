/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeScope.hpp"

namespace Pollux::Lang
{
	ASTNodeScope::ASTNodeScope() noexcept
		:
		ASTNodeBase{ Token{ TokenKind::Undefined, g_pEmptyString } }
	{
		RegisterType("ASTNodeScope", +ASTNodeKind::ASTNodeScope);
	}

	void ASTNodeScope::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}

	void ASTNodeScope::InsertStatement(ASTNodeBase* pStatement)
	{
		pStatements.push_back(pStatement);
	}

	const std::vector<ASTNodeBase*>& ASTNodeScope::GetStatements() const noexcept
	{
		return pStatements;
	}
}