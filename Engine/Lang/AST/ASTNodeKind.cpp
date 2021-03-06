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
	const char* g_ASTNodeKind_ASTNodeFun = "ASTNodeKind::ASTNodeFun";
	const char* g_ASTNodeKind_ASTNodeFunParamDeclStatement = "ASTNodeKind::ASTNodeFunParamDeclStatement";
	const char* g_ASTNodeKind_ASTNodeScope = "ASTNodeKind::ASTNodeScope";
	const char* g_ASTNodeKind_ASTNodeType = "ASTNodeKind::ASTNodeType";
	const char* g_ASTNodeKind_ASTNodeVar = "ASTNodeKind::ASTNodeVar";
	const char* g_ASTNodeKind_ASTNodeSymbol = "ASTNodeKind::ASTNodeSymbol";
	const char* g_ASTNodeKind_ASTNodeTypeSymbol = "ASTNodeKind::ASTNodeTypeSymbol";
	const char* g_ASTNodeKind_ASTNodeVarSymbol = "ASTNodeKind::ASTNodeVarSymbol";
	const char* g_ASTNodeKind_ASTNodeDeclHolder = "ASTNodeKind::ASTNodeDeclHolder";
	const char* g_ASTNodeKind_ASTNodeDeclStatement = "ASTNodeKind::ASTNodeDeclStatement";
	const char* g_ASTNodeKind_ASTNodeIfStatement = "ASTNodeKind::ASTNodeIfStatement";

	const std::map<const char*, ASTNodeKind> g_ASTNodeKindMap
	{
		{ g_ASTNodeKind_ASTNodeBase, ASTNodeKind::ASTNodeBase },
		{ g_ASTNodeKind_ASTNodeAssign, ASTNodeKind::ASTNodeBase },
		{ g_ASTNodeKind_ASTNodeLog, ASTNodeKind::ASTNodeLog },
		{ g_ASTNodeKind_ASTNodeEmptyStatement, ASTNodeKind::ASTNodeEmptyStatement },
		{ g_ASTNodeKind_ASTNodeExpression, ASTNodeKind::ASTNodeExpression },
		{ g_ASTNodeKind_ASTNodeFun, ASTNodeKind::ASTNodeFun },
		{ g_ASTNodeKind_ASTNodeFunParamDeclStatement, ASTNodeKind::ASTNodeFunParamDeclStatement },
		{ g_ASTNodeKind_ASTNodeScope, ASTNodeKind::ASTNodeScope },
		{ g_ASTNodeKind_ASTNodeType, ASTNodeKind::ASTNodeType },
		{ g_ASTNodeKind_ASTNodeVar, ASTNodeKind::ASTNodeVar },
		{ g_ASTNodeKind_ASTNodeSymbol, ASTNodeKind::ASTNodeSymbol },
		{ g_ASTNodeKind_ASTNodeTypeSymbol, ASTNodeKind::ASTNodeTypeSymbol },
		{ g_ASTNodeKind_ASTNodeVarSymbol, ASTNodeKind::ASTNodeVarSymbol },
		{ g_ASTNodeKind_ASTNodeDeclHolder, ASTNodeKind::ASTNodeDeclHolder },
		{ g_ASTNodeKind_ASTNodeDeclStatement, ASTNodeKind::ASTNodeDeclStatement },
		{ g_ASTNodeKind_ASTNodeIfStatement, ASTNodeKind::ASTNodeIfStatement },
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
		case ASTNodeKind::ASTNodeFun: return g_ASTNodeKind_ASTNodeFun;
		case ASTNodeKind::ASTNodeFunParamDeclStatement: return g_ASTNodeKind_ASTNodeFunParamDeclStatement;
		case ASTNodeKind::ASTNodeScope: return g_ASTNodeKind_ASTNodeScope;
		case ASTNodeKind::ASTNodeType: return g_ASTNodeKind_ASTNodeType;
		case ASTNodeKind::ASTNodeVar: return g_ASTNodeKind_ASTNodeVar;
		case ASTNodeKind::ASTNodeSymbol: return g_ASTNodeKind_ASTNodeSymbol;
		case ASTNodeKind::ASTNodeTypeSymbol: return g_ASTNodeKind_ASTNodeTypeSymbol;
		case ASTNodeKind::ASTNodeVarSymbol: return g_ASTNodeKind_ASTNodeVarSymbol;
		case ASTNodeKind::ASTNodeDeclHolder: return g_ASTNodeKind_ASTNodeDeclHolder;
		case ASTNodeKind::ASTNodeDeclStatement: return g_ASTNodeKind_ASTNodeDeclStatement;
		case ASTNodeKind::ASTNodeIfStatement: return g_ASTNodeKind_ASTNodeIfStatement;
		default:; // todo. Log a warning message
		}

		return g_pEmptyString;
	}
}