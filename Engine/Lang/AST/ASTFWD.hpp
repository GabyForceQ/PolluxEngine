/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	class ASTNodeBase;
	class ASTNodeVarSymbol;
	class ASTNodeTypeSymbol;
	class ASTNodeDeclStatement;
	class ASTNodeDeclHolder;
	class ASTNodeType;
	class ASTNodeExpression;
	class ASTNodeScope;
	class ASTNodeAssign;
	class ASTNodeVar;
	class ASTNodeLog;
	class ASTNodeIfStatement;
	class ASTNodeEmptyStatement;
	class ASTNodeFun;
	class ASTNodeFunParamDeclStatement;
}

#define AST_FRIENDS_BODY friend class Parser; \
	friend class SymbolTableBuilder; \
	friend class SemanticAnalyser; \
	friend class CXXCodegen;