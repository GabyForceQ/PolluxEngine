/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../ASTNodeBase.hpp"
#include "../../../Symbol/SymbolKind.hpp"

namespace Pollux::Lang
{
	class ASTNodeSymbol : public ASTNodeBase
	{
	public:
		explicit ASTNodeSymbol(std::string name, SymbolKind symbolKind, ASTNodeTypeSymbol* pTypeSymbol) noexcept;

		const std::string& GetName() const noexcept;

		SymbolKind GetSymbolKind() const noexcept;
		
		const ASTNodeTypeSymbol* GetPTypeSymbol() const noexcept;

	protected:
		std::string name;
		SymbolKind symbolKind = SymbolKind::Undefined;
		ASTNodeTypeSymbol* pTypeSymbol = nullptr;
	};
}