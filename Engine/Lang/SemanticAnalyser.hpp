/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "AST/IASTNodeVisitor.hpp"

namespace Pollux::Lang
{
	class SymbolTable;
	class CompilerUtils;

	class SemanticAnalyser final : public IASTNodeVisitor
	{
	public:
		SemanticAnalyser() noexcept;

		~SemanticAnalyser();

		void Visit(ASTNodeVarSymbol* pNode) override;

		void Visit(ASTNodeTypeSymbol* pNode) override;

		void Visit(ASTNodeDeclStatement* pNode) override;

		void Visit(ASTNodeDeclHolder* pNode) override;

		void Visit(ASTNodeType* pNode) override;

		void Visit(ASTNodeExpression* pNode) override;

		void Visit(ASTNodeScope* pNode) override;

		void Visit(ASTNodeAssign* pNode) override;

		void Visit(ASTNodeVar* pNode) override;

		void Visit(ASTNodeLog* pNode) override;

		void Visit(ASTNodeIfStatement* pNode) override;

		void Visit(ASTNodeEmptyStatement* pNode) override;

		void Visit(ASTNodeFun* pNode) override;

		void Visit(ASTNodeFunParamDeclStatement* pNode) override;

		SymbolTable* pSymbolTable = nullptr;

	private:
		CompilerUtils* pCompilerUtils = nullptr;
	};
}