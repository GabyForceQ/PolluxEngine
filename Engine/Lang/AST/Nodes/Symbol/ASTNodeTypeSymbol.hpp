/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "ASTNodeSymbol.hpp"

namespace Pollux::Lang
{
	class ASTNodeTypeSymbol final : public ASTNodeSymbol
	{
	public:
		explicit ASTNodeTypeSymbol(std::string name, SymbolKind symbolKind, ASTNodeTypeSymbol* pTypeSymbol) noexcept;

		void Accept(IASTNodeVisitor* pVisitor) override;
	};
}