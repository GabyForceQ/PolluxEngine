/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "SymbolTableBuilder.hpp"
#include "SymbolTable.hpp"
#include "../AST/ASTNodes.hpp"

namespace Pollux::Lang
{
	SymbolTableBuilder::SymbolTableBuilder() noexcept
		:
		pSymbolTable{ new SymbolTable() }
	{
	}

	SymbolTableBuilder::~SymbolTableBuilder()
	{
		SAFE_DELETE(pSymbolTable);
	}

	void SymbolTableBuilder::Visit(ASTNodeVarSymbol* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeTypeSymbol* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeDeclStatement* pNode)
	{
		for (ASTNodeDeclHolder* pDeclHolder : pNode->GetDeclHolders())
		{
			pDeclHolder->Accept(this);
		}
	}

	void SymbolTableBuilder::Visit(ASTNodeDeclHolder* pNode)
	{
		const std::string typeName = pNode->pType->token.value;
		ASTNodeTypeSymbol* pTypeSymbol = static_cast<ASTNodeTypeSymbol*>(pSymbolTable->LookUp(typeName));
		const std::string varName = pNode->pAssignment->pHolder->token.value;
		ASTNodeVarSymbol* pVarSymbol =
			new ASTNodeVarSymbol(varName, SymbolKind::Variable, pTypeSymbol, pNode->bComptimeEval);
		
		pSymbolTable->Insert(pTypeSymbol);
	}

	void SymbolTableBuilder::Visit(ASTNodeType* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeExpression* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeScope* pNode)
	{
		for (ASTNodeBase* pStatement : pNode->GetStatements())
		{
			pStatement->Accept(this);
		}
	}

	void SymbolTableBuilder::Visit(ASTNodeAssign* pNode)
	{
		std::string varName = pNode->pHolder->token.value;
		ASTNodeSymbol* pSymbol = pSymbolTable->LookUp(varName);

		if (pSymbol == nullptr)
		{
			std::cout << "Error: variable " << varName << " is used before declaration.\n\n";
		}

		pNode->pExpression->Accept(this);
	}

	void SymbolTableBuilder::Visit(ASTNodeVar* pNode)
	{
		std::string varName = pNode->token.value;
		ASTNodeSymbol* pSymbol = pSymbolTable->LookUp(varName);

		if (pSymbol == nullptr)
		{
			std::cout << "Error: variable " << varName << " is used before declaration.\n\n";
		}
	}

	void SymbolTableBuilder::Visit(ASTNodeLog* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeIfStatement* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeEmptyStatement* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeFun* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeFunParamDeclStatement* pNode)
	{
	}

	void SymbolTableBuilder::Visit(ASTNodeReturn* pNode)
	{
	}
}