/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeTypeSymbol.hpp"

namespace Pollux::Lang
{
	ASTNodeTypeSymbol::ASTNodeTypeSymbol(std::string name, SymbolKind symbolKind, ASTNodeTypeSymbol* pTypeSymbol) noexcept
		:
		ASTNodeSymbol{ std::move(name), std::move(symbolKind), pTypeSymbol }
	{
		RegisterType("ASTNodeTypeSymbol", +ASTNodeKind::ASTNodeTypeSymbol);
	}

	void ASTNodeTypeSymbol::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}