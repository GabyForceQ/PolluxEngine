/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	class ASTNodeVarSymbol;
	class ASTNodeTypeSymbol;
	class ASTNodeDeclStatement;
	class ASTNodeDeclHolder;
	class ASTNodeType;
	class ASTNodeExpression;
	class ASTNodeCompound;
	class ASTNodeAssign;
	class ASTNodeVar;
	class ASTNodeLog;
	class ASTNodeIfStatement;
	class ASTNodeFunction;
	class ASTNodeEmptyStatement;

	class IASTNodeVisitor
	{
	public:
		virtual void Visit(ASTNodeVarSymbol* pNode) = 0;
		
		virtual void Visit(ASTNodeTypeSymbol* pNode) = 0;
		
		virtual void Visit(ASTNodeDeclStatement* pNode) = 0;
		
		virtual void Visit(ASTNodeDeclHolder* pNode) = 0;
		
		virtual void Visit(ASTNodeType* pNode) = 0;
		
		virtual void Visit(ASTNodeExpression* pNode) = 0;
		
		virtual void Visit(ASTNodeCompound* pNode) = 0;
		
		virtual void Visit(ASTNodeAssign* pNode) = 0;
		
		virtual void Visit(ASTNodeVar* pNode) = 0;
		
		virtual void Visit(ASTNodeLog* pNode) = 0;
		
		virtual void Visit(ASTNodeIfStatement* pNode) = 0;
		
		virtual void Visit(ASTNodeFunction* pNode) = 0;
		
		virtual void Visit(ASTNodeEmptyStatement* pNode) = 0;
	};
}