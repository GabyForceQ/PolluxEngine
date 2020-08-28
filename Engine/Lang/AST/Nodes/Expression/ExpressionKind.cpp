/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ExpressionKind.hpp"

namespace Pollux::Lang
{
	const char* g_pExpressionKind_Unit = "ExpressionKind::Unit";
	const char* g_pExpressionKind_NumberLiteral = "ExpressionKind::NumberLiteral";
	const char* g_pExpressionKind_StringLiteral = "ExpressionKind::StringLiteral";
	const char* g_pExpressionKind_DynamicHolder = "ExpressionKind::DynamicHolder";
	const char* g_pExpressionKind_Unary = "ExpressionKind::Unary";
	const char* g_pExpressionKind_Binary = "ExpressionKind::Binary";

	const std::map<const char*, ExpressionKind> g_ExpressionKindMap
	{
		{ g_pExpressionKind_Unit, ExpressionKind::Unit },
		{ g_pExpressionKind_NumberLiteral, ExpressionKind::NumberLiteral },
		{ g_pExpressionKind_StringLiteral, ExpressionKind::StringLiteral },
		{ g_pExpressionKind_DynamicHolder, ExpressionKind::DynamicHolder },
		{ g_pExpressionKind_Unary, ExpressionKind::Unary },
		{ g_pExpressionKind_Binary, ExpressionKind::Binary }
	};

	ExpressionKind ExpressionKindToEnum(const char* expressionKind)
	{
		if (g_ExpressionKindMap.contains(expressionKind))
		{
			return g_ExpressionKindMap.at(expressionKind);
		}

		throw std::runtime_error("Error (Lang.AST): ExpressionKind string is not valid.");
	}

	std::string ToString(const ExpressionKind expressionKind)
	{
		switch (expressionKind)
		{
		case ExpressionKind::Unit: return g_pExpressionKind_Unit;
		case ExpressionKind::NumberLiteral: return g_pExpressionKind_NumberLiteral;
		case ExpressionKind::StringLiteral: return g_pExpressionKind_StringLiteral;
		case ExpressionKind::DynamicHolder: return g_pExpressionKind_DynamicHolder;
		case ExpressionKind::Unary: return g_pExpressionKind_Unary;
		case ExpressionKind::Binary: return g_pExpressionKind_Binary;
		default:; // todo. Log a warning message
		}

		return g_pEmptyString;
	}
}