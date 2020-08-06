/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "ASTNodeSymbol.hpp"

namespace Pollux::Lang
{
	class ASTNodeVarSymbol final : public ASTNodeSymbol
	{
	public:
		explicit ASTNodeVarSymbol(std::string name, SymbolKind symbolKind,
			ASTNodeTypeSymbol* pTypeSymbol, bool bComptimeEval = false) noexcept;

		void Accept(IASTNodeVisitor* pVisitor) override;

		const std::string& GetValue() const noexcept;
		
		bool IsComptimeEval() const noexcept;

	private:
		std::string value;
		bool bComptimeEval = false;

		AST_FRIENDS_BODY
	};
}