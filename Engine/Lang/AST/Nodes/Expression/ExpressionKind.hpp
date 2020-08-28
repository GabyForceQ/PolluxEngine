/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	enum class ExpressionKind
	{
		Unit,
		NumberLiteral,
		StringLiteral,
		DynamicHolder,
		Unary,
		Binary
	};

	extern const char* g_pExpressionKind_Unit;

	extern const char* g_pExpressionKind_NumberLiteral;

	extern const char* g_pExpressionKind_StringLiteral;

	extern const char* g_pExpressionKind_DynamicHolder;

	extern const char* g_pExpressionKind_Unary;

	extern const char* g_pExpressionKind_Binary;

	extern const std::map<const char*, ExpressionKind> g_ExpressionKindMap;

	ExpressionKind ExpressionKindToEnum(const char* expressionKind);

	std::string ToString(const ExpressionKind expressionKind);
}