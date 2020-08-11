/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "SemanticAnalyser.hpp"
#include "CompilerUtils.hpp"
#include "Symbol/SymbolTable.hpp"
#include "AST/ASTNodes.hpp"

namespace Pollux::Lang
{
	SemanticAnalyser::SemanticAnalyser() noexcept
		:
		pSymbolTable{ new SymbolTable() },
		pCompilerUtils{ new CompilerUtils() }
	{
	}

	SemanticAnalyser::~SemanticAnalyser()
	{
		SAFE_DELETE(pSymbolTable);
		SAFE_DELETE(pCompilerUtils);
	}

	void SemanticAnalyser::Visit(ASTNodeVarSymbol* pNode)
	{
	}

	void SemanticAnalyser::Visit(ASTNodeTypeSymbol* pNode)
	{
	}

	void SemanticAnalyser::Visit(ASTNodeDeclStatement* pNode)
	{
		for (ASTNodeDeclHolder* pDeclHolder : pNode->GetDeclHolders())
		{
			pDeclHolder->Accept(this);
		}
	}

	void SemanticAnalyser::Visit(ASTNodeDeclHolder* pNode)
	{
		pNode->pAssignment->pExpression->Accept(this);

		if (pNode->bAutoDeduction)
		{
			// todo. improve for vars too
			if (pCompilerUtils->IsBoolean(pNode->pAssignment->pExpression->token.value))
			{
				pNode->pType = new ASTNodeType(Token{ TokenKind::Identifier, "Bool" });
			}
			else if (pCompilerUtils->IsInteger(pNode->pAssignment->pExpression->token.value))
			{
				pNode->pType = new ASTNodeType(Token{ TokenKind::Identifier, "Int" });
			}
			else if (pCompilerUtils->IsString(pNode->pAssignment->pExpression->token.value))
			{
				pNode->pType = new ASTNodeType(Token{ TokenKind::Identifier, "String" });
			}
		}

		const std::string typeName = pNode->pType->token.value;
		ASTNodeTypeSymbol* pTypeSymbol = static_cast<ASTNodeTypeSymbol*>(pSymbolTable->LookUp(typeName));
		const std::string varName = pNode->pAssignment->pHolder->token.value;
		SymbolKind symbolKind = pNode->bComptimeEval ? SymbolKind::Constant : SymbolKind::Variable;
		ASTNodeVarSymbol* pVarSymbol = new ASTNodeVarSymbol(varName, symbolKind, pTypeSymbol, pNode->bComptimeEval);

		if (pSymbolTable->LookUp(varName) != nullptr)
		{
			std::cout << "Semantic Error: Duplicate identifier: " << varName << "\n";
		}

		pSymbolTable->Insert(pVarSymbol);
	}

	void SemanticAnalyser::Visit(ASTNodeType* pNode)
	{
	}

	void SemanticAnalyser::Visit(ASTNodeExpression* pNode)
	{
	}

	void SemanticAnalyser::Visit(ASTNodeScope* pNode)
	{
		for (ASTNodeBase* pStatement : pNode->GetStatements())
		{
			pStatement->Accept(this);
		}
	}

	void SemanticAnalyser::Visit(ASTNodeAssign* pNode)
	{
		// Right-hand side.
		pNode->pExpression->Accept(this);
		// Left-hand side.
		pNode->pHolder->Accept(this);

		ASTNodeVarSymbol* pVarSymbol =
			static_cast<ASTNodeVarSymbol*>(pSymbolTable->LookUp(pNode->pHolder->token.value));
		
		if (pVarSymbol->IsComptimeEval())
		{
			std::cout << "Semantic Error: Cannot modify a constant declaration.\n\n";
		}

		if (pNode->token.kind == TokenKind::OperatorDivAssign && pNode->pExpression->token.value == "0")
		{
			std::cout << "Semantic Error: Cannot divide integer by 0.\n\n";
		}
	}

	void SemanticAnalyser::Visit(ASTNodeVar* pNode)
	{
		const std::string varName = pNode->token.value;
		ASTNodeSymbol* pSymbol = pSymbolTable->LookUp(varName);

		if (pSymbol == nullptr)
		{
			std::cout << "Semantic Error: variable " << varName << " is not defined.\n\n";
		}
	}

	void SemanticAnalyser::Visit(ASTNodeLog* pNode)
	{
	}

	void SemanticAnalyser::Visit(ASTNodeIfStatement* pNode)
	{
		pNode->pExpression->Accept(this);
		pNode->pIfScope->Accept(this);
		
		for (const auto& e : pNode->pElseIfScopes)
		{
			e.first->Accept(this);
		}

		if (pNode->pElseScope != nullptr)
		{
			pNode->pElseScope->Accept(this);
		}
	}

	void SemanticAnalyser::Visit(ASTNodeEmptyStatement* pNode)
	{
	}

	void SemanticAnalyser::Visit(ASTNodeFun* pNode)
	{
		// todo. accept prototype

		// Accept fun scope
		pNode->pScope->Accept(this);

	}

	void SemanticAnalyser::Visit(ASTNodeFunParamDeclStatement* pNode)
	{
	}

	void SemanticAnalyser::Visit(ASTNodeReturn* pNode)
	{
		pNode->pExpression->Accept(this);

		//if (pNode->pReturnType->value != pNode->pFunction->pReturnType->value)
		//{
		//	std::cout << "Semantic Error: --------.\n\n";
		//}
	}
}