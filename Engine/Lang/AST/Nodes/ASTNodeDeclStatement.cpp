/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeDeclStatement.hpp"

namespace Pollux::Lang
{
	ASTNodeDeclStatement::ASTNodeDeclStatement(const std::deque<ASTNodeDeclHolder*>& pDeclHolders, bool bComptimeEval) noexcept
		:
		ASTNodeBase{ Token{ TokenKind::Undefined, g_pEmptyString } },
		pDeclHolders{ pDeclHolders },
		bComptimeEval{ std::move(bComptimeEval) }
	{
		RegisterType("ASTNodeDeclStatement", +ASTNodeKind::ASTNodeDeclStatement);
	}

	void ASTNodeDeclStatement::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}

	const std::deque<ASTNodeDeclHolder*> ASTNodeDeclStatement::GetDeclHolders() const noexcept
	{
		return pDeclHolders;
	}

	bool ASTNodeDeclStatement::IsComptimeEval() const noexcept
	{
		return bComptimeEval;
	}
}