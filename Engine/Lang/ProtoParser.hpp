/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "Tokenizer/TokenKind.hpp"

namespace Pollux::Lang
{
	class Parser;
	struct ParseContext;
	struct PxSymbolTable;
	struct Token;

	class PxSymbolParser final
	{
	public:
		explicit PxSymbolParser(Parser* pParser) noexcept;

		PxSymbolTable* ParseScopeMembers();

	private:
		void ParseUsage(PxSymbolTable* pSymbolTable, const TokenKind tokenKind);
		void ParseAccess(PxSymbolTable* pSymbolTable, const TokenKind tokenKind);
		void BeginSymbol(PxSymbolTable* pSymbolTable, const TokenKind tokenKind);
		void RegisterSymbol(PxSymbolTable* pSymbolTable, const TokenKind tokenKind);

		Parser* m_pParser = nullptr;
		PxSymbolTable* m_pSymbolTable = nullptr;
		ParseContext* m_pContext = nullptr;
	};
}