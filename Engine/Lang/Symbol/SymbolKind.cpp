/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "SymbolKind.hpp"

namespace Pollux::Lang
{
	const char* g_pSymbolKind_KeywordUndefined = "SymbolKind::Undefined";
	const char* g_pSymbolKind_KeywordPrimitiveType = "SymbolKind::PrimitiveType";
	const char* g_pSymbolKind_KeywordVariable = "SymbolKind::Variable";
	const char* g_pSymbolKind_KeywordConstant = "SymbolKind::Constant";
	const char* g_pSymbolKind_KeywordComptimeVariable = "SymbolKind::ComptimeVariable";
	const char* g_pSymbolKind_KeywordComptimeConstant = "SymbolKind::ComptimeConstant";

	const std::map<const char*, SymbolKind> g_SymbolKindMap
	{
		{ g_pSymbolKind_KeywordUndefined, SymbolKind::Undefined },
		{ g_pSymbolKind_KeywordPrimitiveType, SymbolKind::PrimitiveType },
		{ g_pSymbolKind_KeywordVariable, SymbolKind::Variable },
		{ g_pSymbolKind_KeywordConstant, SymbolKind::Constant },
		{ g_pSymbolKind_KeywordComptimeVariable, SymbolKind::ComptimeVariable },
		{ g_pSymbolKind_KeywordComptimeConstant, SymbolKind::ComptimeConstant }
	};

	SymbolKind SymbolKindToEnum(const char* symbolKind)
	{
		if (g_SymbolKindMap.contains(symbolKind))
		{
			return g_SymbolKindMap.at(symbolKind);
		}

		throw std::runtime_error("Error (Lang.Symbol): SymbolKind string is not valid.");
	}

	std::string ToString(const SymbolKind symbolKind)
	{
		switch (symbolKind)
		{
		case SymbolKind::Undefined: return g_pSymbolKind_KeywordUndefined;
		case SymbolKind::PrimitiveType: return g_pSymbolKind_KeywordPrimitiveType;
		case SymbolKind::Variable: return g_pSymbolKind_KeywordVariable;
		case SymbolKind::Constant: return g_pSymbolKind_KeywordConstant;
		case SymbolKind::ComptimeVariable: return g_pSymbolKind_KeywordComptimeVariable;
		case SymbolKind::ComptimeConstant: return g_pSymbolKind_KeywordComptimeConstant;
		}

		return g_pEmptyString;
	}
}