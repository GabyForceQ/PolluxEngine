/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeKind.hpp"

namespace Pollux::Lang
{
	const char* g_ASTNodeKind_ASTNodeBase = "ASTNodeKind::ASTNodeBase";
	const char* g_ASTNodeKind_ASTNodeAssign = "ASTNodeKind::ASTNodeAssign";
	const char* g_ASTNodeKind_ASTNodeLog = "ASTNodeKind::ASTNodeLog";
	const char* g_ASTNodeKind_ASTNodeEmptyStatement = "ASTNodeKind::ASTNodeEmptyStatement";
	const char* g_ASTNodeKind_ASTNodeExpression = "ASTNodeKind::ASTNodeExpression";
	const char* g_ASTNodeKind_ASTNodeFunction = "ASTNodeKind::ASTNodeFunction";
	const char* g_ASTNodeKind_ASTNodeScope = "ASTNodeKind::ASTNodeScope";
	const char* g_ASTNodeKind_ASTNodeType = "ASTNodeKind::ASTNodeType";
	const char* g_ASTNodeKind_ASTNodeVariable = "ASTNodeKind::ASTNodeVariable";
	const char* g_ASTNodeKind_ASTNodeSymbol = "ASTNodeKind::ASTNodeSymbol";
	const char* g_ASTNodeKind_ASTNodeTypeSymbol = "ASTNodeKind::ASTNodeTypeSymbol";
	const char* g_ASTNodeKind_ASTNodeVarSymbol = "ASTNodeKind::ASTNodeVarSymbol";
	const char* g_ASTNodeKind_ASTNodeDeclHolder = "ASTNodeKind::ASTNodeDeclHolder";
	const char* g_ASTNodeKind_ASTNodeDeclStatement = "ASTNodeKind::ASTNodeDeclStatement";
	const char* g_ASTNodeKind_ASTNodeIfElse = "ASTNodeKind::ASTNodeIfElse";

	const std::map<const char*, ASTNodeKind> g_ASTNodeKindMap
	{
		{ g_ASTNodeKind_ASTNodeBase, ASTNodeKind::ASTNodeBase },
		{ g_ASTNodeKind_ASTNodeAssign, ASTNodeKind::ASTNodeBase },
		{ g_ASTNodeKind_ASTNodeLog, ASTNodeKind::ASTNodeLog },
		{ g_ASTNodeKind_ASTNodeEmptyStatement, ASTNodeKind::ASTNodeEmptyStatement },
		{ g_ASTNodeKind_ASTNodeExpression, ASTNodeKind::ASTNodeExpression },
		{ g_ASTNodeKind_ASTNodeFunction, ASTNodeKind::ASTNodeFunction },
		{ g_ASTNodeKind_ASTNodeScope, ASTNodeKind::ASTNodeScope },
		{ g_ASTNodeKind_ASTNodeType, ASTNodeKind::ASTNodeType },
		{ g_ASTNodeKind_ASTNodeVariable, ASTNodeKind::ASTNodeVariable },
		{ g_ASTNodeKind_ASTNodeSymbol, ASTNodeKind::ASTNodeSymbol },
		{ g_ASTNodeKind_ASTNodeTypeSymbol, ASTNodeKind::ASTNodeTypeSymbol },
		{ g_ASTNodeKind_ASTNodeVarSymbol, ASTNodeKind::ASTNodeVarSymbol },
		{ g_ASTNodeKind_ASTNodeDeclHolder, ASTNodeKind::ASTNodeDeclHolder },
		{ g_ASTNodeKind_ASTNodeDeclStatement, ASTNodeKind::ASTNodeDeclStatement },
		{ g_ASTNodeKind_ASTNodeIfElse, ASTNodeKind::ASTNodeIfElse },
	};

	ASTNodeKind ASTNodeKindToEnum(const char* astNodeKind)
	{
		if (g_ASTNodeKindMap.contains(astNodeKind))
		{
			return g_ASTNodeKindMap.at(astNodeKind);
		}

		throw std::runtime_error("Error (Lang.AST): ASTNodeKind string is not valid.");
	}

	std::string ToString(const ASTNodeKind astNodeKind)
	{
		switch (astNodeKind)
		{
		case ASTNodeKind::ASTNodeBase: return g_ASTNodeKind_ASTNodeBase;
		case ASTNodeKind::ASTNodeAssign: return g_ASTNodeKind_ASTNodeAssign;
		case ASTNodeKind::ASTNodeLog: return g_ASTNodeKind_ASTNodeLog;
		case ASTNodeKind::ASTNodeEmptyStatement: return g_ASTNodeKind_ASTNodeEmptyStatement;
		case ASTNodeKind::ASTNodeExpression: return g_ASTNodeKind_ASTNodeExpression;
		case ASTNodeKind::ASTNodeFunction: return g_ASTNodeKind_ASTNodeFunction;
		case ASTNodeKind::ASTNodeScope: return g_ASTNodeKind_ASTNodeScope;
		case ASTNodeKind::ASTNodeType: return g_ASTNodeKind_ASTNodeType;
		case ASTNodeKind::ASTNodeVariable: return g_ASTNodeKind_ASTNodeVariable;
		case ASTNodeKind::ASTNodeSymbol: return g_ASTNodeKind_ASTNodeSymbol;
		case ASTNodeKind::ASTNodeTypeSymbol: return g_ASTNodeKind_ASTNodeTypeSymbol;
		case ASTNodeKind::ASTNodeVarSymbol: return g_ASTNodeKind_ASTNodeVarSymbol;
		case ASTNodeKind::ASTNodeDeclHolder: return g_ASTNodeKind_ASTNodeDeclHolder;
		case ASTNodeKind::ASTNodeDeclStatement: return g_ASTNodeKind_ASTNodeDeclStatement;
		case ASTNodeKind::ASTNodeIfElse: return g_ASTNodeKind_ASTNodeIfElse;
		default:; // todo. Log a warning message
		}

		return g_pEmptyString;
	}
}