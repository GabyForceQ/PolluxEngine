/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeSymbol.hpp"

namespace Pollux::Lang
{
	ASTNodeSymbol::ASTNodeSymbol(std::string name, SymbolKind symbolKind, ASTNodeTypeSymbol* pTypeSymbol) noexcept
		:
		ASTNodeBase{ Token{ TokenKind::Undefined, g_pEmptyString } },
		name{ std::move(name) },
		symbolKind{ std::move(symbolKind) },
		pTypeSymbol{ pTypeSymbol }
	{
		RegisterType("ASTNodeSymbol", +ASTNodeKind::ASTNodeSymbol);
	}

	const std::string& ASTNodeSymbol::GetName() const noexcept
	{
		return name;
	}

	SymbolKind ASTNodeSymbol::GetSymbolKind() const noexcept
	{
		return symbolKind;
	}

	const ASTNodeTypeSymbol* ASTNodeSymbol::GetPTypeSymbol() const noexcept
	{
		return pTypeSymbol;
	}
}