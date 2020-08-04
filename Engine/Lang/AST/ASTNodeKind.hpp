/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	enum class ASTNodeKind : type_t
	{
		ASTNodeBase,
		ASTNodeAssign,
		ASTNodeLog,
		ASTNodeEmptyStatement,
		ASTNodeExpression,
		ASTNodeFunction,
		ASTNodeScope,
		ASTNodeType,
		ASTNodeVar,
		ASTNodeSymbol,
		ASTNodeTypeSymbol,
		ASTNodeVarSymbol,
		ASTNodeDeclHolder,
		ASTNodeDeclStatement,
		ASTNodeIfElse
	};

	MAKE_ENUM_CONVERTIBLE_TO(ASTNodeKind, type_t)

	extern const char* g_ASTNodeKind_ASTNodeBase;
	extern const char* g_ASTNodeKind_ASTNodeAssign;
	extern const char* g_ASTNodeKind_ASTNodeLog;
	extern const char* g_ASTNodeKind_ASTNodeEmptyStatement;
	extern const char* g_ASTNodeKind_ASTNodeExpression;
	extern const char* g_ASTNodeKind_ASTNodeFunction;
	extern const char* g_ASTNodeKind_ASTNodeScope;
	extern const char* g_ASTNodeKind_ASTNodeType;
	extern const char* g_ASTNodeKind_ASTNodeVar;
	extern const char* g_ASTNodeKind_ASTNodeSymbol;
	extern const char* g_ASTNodeKind_ASTNodeTypeSymbol;
	extern const char* g_ASTNodeKind_ASTNodeVarSymbol;
	extern const char* g_ASTNodeKind_ASTNodeDeclHolder;
	extern const char* g_ASTNodeKind_ASTNodeDeclStatement;
	extern const char* g_ASTNodeKind_ASTNodeIfElse;

	extern const std::map<const char*, ASTNodeKind> g_ASTNodeKindMap;

	ASTNodeKind ASTNodeKindToEnum(const char* astNodeKind);
	std::string ToString(const ASTNodeKind astNodeKind);
}