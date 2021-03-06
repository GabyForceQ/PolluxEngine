/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeVarSymbol.hpp"

namespace Pollux::Lang
{
	ASTNodeVarSymbol::ASTNodeVarSymbol(std::string name, SymbolKind symbolKind,
		ASTNodeTypeSymbol* pTypeSymbol, bool bComptimeEval) noexcept
		:
		ASTNodeSymbol{ std::move(name), std::move(symbolKind), pTypeSymbol },
		bComptimeEval{ std::move(bComptimeEval) }
	{
		RegisterType("ASTNodeVarSymbol", +ASTNodeKind::ASTNodeVarSymbol);
	}

	void ASTNodeVarSymbol::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}

	const std::string& ASTNodeVarSymbol::GetValue() const noexcept
	{
		return value;
	}

	bool ASTNodeVarSymbol::IsComptimeEval() const noexcept
	{
		return bComptimeEval;
	}
}