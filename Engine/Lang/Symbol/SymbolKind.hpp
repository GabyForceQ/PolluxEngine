/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	/*************************************************************************************************************************
	 * \enum Symbol Kind
	 *************************************************************************************************************************/
	enum class SymbolKind
	{
		Undefined,
		PrimitiveType,
		Variable,
		Constant,
		ComptimeVariable,
		ComptimeConstant
		//AlwaysVariable,
		//AlwaysConstant
	};

	extern const char* g_pSymbolKind_KeywordUndefined;

	extern const char* g_pSymbolKind_KeywordPrimitiveType;

	extern const char* g_pSymbolKind_KeywordVariable;

	extern const char* g_pSymbolKind_KeywordConstant;

	extern const char* g_pSymbolKind_KeywordComptimeVariable;

	extern const char* g_pSymbolKind_KeywordComptimeConstant;

	extern const std::map<const char*, SymbolKind> g_SymbolKindMap;

	SymbolKind SymbolKindToEnum(const char* symbolKind);

	std::string ToString(const SymbolKind symbolKind);
}