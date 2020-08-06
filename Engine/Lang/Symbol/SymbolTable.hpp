/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	class ASTNodeSymbol;

	class SymbolTable final
	{
	public:
		SymbolTable() noexcept;

		void Insert(ASTNodeSymbol* pSymbol);

		ASTNodeSymbol* LookUp(const std::string& name);

		std::string ToString();

		std::unordered_map<std::string, ASTNodeSymbol*> pSymbolMap;
	};
}