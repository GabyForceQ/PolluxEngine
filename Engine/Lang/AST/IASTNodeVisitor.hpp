/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	class IASTNodeVisitor
	{
	public:
		virtual void Visit(class ASTNodeVarSymbol* pNode) = 0;
		
		virtual void Visit(class ASTNodeTypeSymbol* pNode) = 0;
		
		virtual void Visit(class ASTNodeDeclStatement* pNode) = 0;
		
		virtual void Visit(class ASTNodeDeclHolder* pNode) = 0;
		
		virtual void Visit(class ASTNodeType* pNode) = 0;
		
		virtual void Visit(class ASTNodeExpression* pNode) = 0;
		
		virtual void Visit(class ASTNodeCompound* pNode) = 0;
		
		virtual void Visit(class ASTNodeAssign* pNode) = 0;
		
		virtual void Visit(class ASTNodeVariable* pNode) = 0;
		
		virtual void Visit(class ASTNodeLog* pNode) = 0;
		
		virtual void Visit(class ASTNodeIfStatement* pNode) = 0;
		
		virtual void Visit(class ASTNodeFunction* pNode) = 0;
		
		virtual void Visit(class ASTNodeEmptyStatement* pNode) = 0;
	};
}