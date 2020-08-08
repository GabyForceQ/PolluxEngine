/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "CXXCodegen.hpp"
#include "CXXCompilerUtils.hpp"
#include "../CompilerUtils.hpp"
#include "../Symbol/SymbolTable.hpp"
#include "../AST/ASTNodes.hpp"

namespace Pollux::Lang
{
	CXXCodegen::CXXCodegen(SymbolTable* pSymbolTable) noexcept
		:
		pSymbolTable{ pSymbolTable },
		pCompilerUtils{ new CompilerUtils() },
		pCXXCompilerUtils{ new CXXCompilerUtils() }
	{
	}

	CXXCodegen::~CXXCodegen()
	{
		SAFE_DELETE(pCompilerUtils);
		SAFE_DELETE(pCXXCompilerUtils);
	}

	void CXXCodegen::Visit(ASTNodeVarSymbol* pNode)
	{
	}

	void CXXCodegen::Visit(ASTNodeTypeSymbol* pNode)
	{
	}

	void CXXCodegen::Visit(ASTNodeDeclStatement* pNode)
	{
		std::string statementCode;

		for (ASTNodeDeclHolder* pDeclHolder : pNode->GetDeclHolders())
		{
			pDeclHolder->Accept(this);
			statementCode += generatedCode + ";\n";
		}

		generatedCode = statementCode;
	}

	void CXXCodegen::Visit(ASTNodeDeclHolder* pNode)
	{
		pNode->pAssignment->pExpression->Accept(this);
		std::string expressionCode = generatedCode;

		pNode->pType->Accept(this);
		std::string typeCode = generatedCode;

		pNode->pAssignment->pHolder->Accept(this);
		std::string holderCode = generatedCode;

		if (pNode->bComptimeEval)
		{
			static_cast<ASTNodeVarSymbol*>(pSymbolTable->pSymbolMap[holderCode])->bComptimeEval = true;

			if (!pCompilerUtils->IsBoolean(expressionCode) &&
				!pCompilerUtils->IsInteger(expressionCode) &&
				!pCompilerUtils->IsString(expressionCode))
			{
				std::cout << "CXXCompiler Error: Cannot assign a variable expresion to a constant declaration.\n\n";
			}

			pSymbolTable->pSymbolMap[holderCode]->content = expressionCode;
		}

		generatedCode = typeCode + " " + holderCode + "=" + expressionCode;
	}

	void CXXCodegen::Visit(ASTNodeType* pNode)
	{
		generatedCode = pCXXCompilerUtils->ToPrimitive(pNode->token.value);
	}

	void CXXCodegen::Visit(ASTNodeExpression* pNode)
	{
		switch (pNode->kind)
		{
		case ExpressionKind::NumberLiteral:
		case ExpressionKind::StringLiteral:
		{
			generatedCode = pNode->token.value;
			break;
		}
		case ExpressionKind::DynamicHolder:
		{
			if (!pCompilerUtils->IsInteger(pNode->token.value) &&
				!pCompilerUtils->IsBoolean(pNode->token.value) &&
				!pCompilerUtils->IsString(pNode->token.value) &&
				!pCompilerUtils->IsSubExpression(pNode->token.value))
			{
				if (static_cast<ASTNodeVarSymbol*>(pSymbolTable->pSymbolMap[pNode->token.value])->bComptimeEval)
				{
					generatedCode = pSymbolTable->pSymbolMap[pNode->token.value]->content;
					return;
				}
			}

			generatedCode = pNode->token.value;
			break;
		}
		case ExpressionKind::Unary:
		{
			pNode->pUnaryOp->Accept(this);

			if (pNode->token.kind == TokenKind::OperatorSub)
			{
				generatedCode = "(" + pNode->token.value + generatedCode + ")";
			}
			else if (pCompilerUtils->IsBoolean(generatedCode))
			{
				if (pNode->token.kind == TokenKind::LogicalNot)
				{
					generatedCode = (generatedCode == "true" ? "false" : "true");
				}
			}
			else if (pNode->token.kind == TokenKind::LogicalNot)
			{
				generatedCode = "(" + pNode->token.value + generatedCode + ")";
			}

			break;
		}
		case ExpressionKind::Binary:
		{
			pNode->pBinaryOpLeft->Accept(this);
			std::string leftCode = generatedCode;

			pNode->pBinaryOpRight->Accept(this);
			std::string rightCode = generatedCode;

			if (pCompilerUtils->IsInteger(leftCode) && pCompilerUtils->IsInteger(rightCode))
			{
				pCompilerUtils->RemoveParensIf(leftCode);
				pCompilerUtils->RemoveParensIf(rightCode);

				if (pNode->token.kind == TokenKind::OperatorAdd)
				{
					int32_t res = atoi(leftCode.c_str()) + atoi(rightCode.c_str());
					generatedCode = std::to_string(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorSub)
				{
					int32_t res = atoi(leftCode.c_str()) - atoi(rightCode.c_str());
					generatedCode = std::to_string(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorMul)
				{
					int32_t res = atoi(leftCode.c_str()) * atoi(rightCode.c_str());
					generatedCode = std::to_string(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorDiv)
				{
					int32_t res = atoi(leftCode.c_str()) / atoi(rightCode.c_str());
					generatedCode = std::to_string(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorMod)
				{
					int32_t res = atoi(leftCode.c_str()) % atoi(rightCode.c_str());
					generatedCode = std::to_string(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorPow)
				{
					int32_t res = static_cast<int32_t>(pow(atoi(leftCode.c_str()), atoi(rightCode.c_str())));
					generatedCode = std::to_string(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorRoot)
				{
					int32_t res = static_cast<int32_t>(pow(atoi(leftCode.c_str()), 1.0 / atoi(rightCode.c_str())));
					generatedCode = std::to_string(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorEq)
				{
					bool res = atoi(leftCode.c_str()) == atoi(rightCode.c_str());
					generatedCode = pCompilerUtils->BoolToString(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorNe)
				{
					bool res = atoi(leftCode.c_str()) != atoi(rightCode.c_str());
					generatedCode = pCompilerUtils->BoolToString(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorLe)
				{
					bool res = atoi(leftCode.c_str()) <= atoi(rightCode.c_str());
					generatedCode = pCompilerUtils->BoolToString(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorLt)
				{
					bool res = atoi(leftCode.c_str()) < atoi(rightCode.c_str());
					generatedCode = pCompilerUtils->BoolToString(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorGe)
				{
					bool res = atoi(leftCode.c_str()) >= atoi(rightCode.c_str());
					generatedCode = pCompilerUtils->BoolToString(res);
				}
				else if (pNode->token.kind == TokenKind::OperatorGt)
				{
					bool res = atoi(leftCode.c_str()) > atoi(rightCode.c_str());
					generatedCode = pCompilerUtils->BoolToString(res);
				}
			}
			else if (pCompilerUtils->IsBoolean(leftCode) && pCompilerUtils->IsBoolean(rightCode))
			{
				bool res = false;
				bool leftVal = (leftCode == "true" ? true : false);
				bool rightVal = (rightCode == "true" ? true : false);

				if (pNode->token.kind == TokenKind::LogicalAnd)
				{
					res = leftVal && rightVal;
				}
				else if (pNode->token.kind == TokenKind::LogicalOr)
				{
					res = leftVal || rightVal;
				}
				else if (pNode->token.kind == TokenKind::OperatorEq)
				{
					res = leftVal == rightVal;
				}
				else if (pNode->token.kind == TokenKind::OperatorNe)
				{
					res = leftVal != rightVal;
				}

				generatedCode = (res ? "true" : "false");
			}
			else if (pCompilerUtils->IsString(leftCode) && pCompilerUtils->IsString(rightCode))
			{
				if (pNode->token.kind == TokenKind::OperatorAdd)
				{
					generatedCode = pCompilerUtils->CombineStrings(leftCode, rightCode);
				}
			}
			else
			{
				if (pNode->token.kind == TokenKind::OperatorPow)
				{
					generatedCode = "std::pow(" + leftCode + "," + rightCode + ")";
				}
				else if (pNode->token.kind == TokenKind::OperatorRoot)
				{
					if (pCompilerUtils->IsInteger(rightCode))
					{
						double rightInvRoot = 1.0 / atoi(rightCode.c_str());
						std::string rightInvRootStr = std::to_string(rightInvRoot);
						pCompilerUtils->RemoveLastZerosFromFloat(rightInvRootStr);
						generatedCode = "std::pow(" + leftCode + "," + rightInvRootStr + ")";
					}
					else
					{
						generatedCode = "std::pow(" + leftCode + ",1.0/" + rightCode + ")";
					}
				}
				else
				{
					generatedCode = "(" + leftCode + pNode->token.value + rightCode + ")";
				}
			}

			break;
		}
		default: throw std::runtime_error("");
		}
	}

	void CXXCodegen::Visit(ASTNodeScope* pNode)
	{
		std::string statementCode;

		for (ASTNodeBase* pStatement : pNode->pStatements)
		{
			pStatement->Accept(this);

			if (generatedCode.length())
			{
				statementCode += generatedCode + (generatedCode[generatedCode.length() - 1] == ';' ?
					"\n" : (generatedCode[generatedCode.length() - 1] != '\n' ? ";\n" : ""));
			}
		}

		generatedCode = statementCode;
	}

	void CXXCodegen::Visit(ASTNodeAssign* pNode)
	{
		// Right-hand side.
		pNode->pExpression->Accept(this);
		std::string exprCode = generatedCode;

		// Left-hand side.
		pNode->pHolder->Accept(this);
		std::string holderCode = generatedCode;
		pCompilerUtils->RemoveParensIf(exprCode);

		if (pNode->token.kind == TokenKind::OperatorPowAssign)
		{
			generatedCode = holderCode + "=std::pow(" + holderCode + "," + exprCode + ")";
		}
		else if (pNode->token.kind == TokenKind::OperatorRootAssign)
		{
			if (pCompilerUtils->IsInteger(exprCode))
			{
				double rightInvRoot = 1.0 / atoi(exprCode.c_str());
				std::string rightInvRootStr = std::to_string(rightInvRoot);
				
				pCompilerUtils->RemoveLastZerosFromFloat(rightInvRootStr);
				
				generatedCode = holderCode + "=std::pow(" + holderCode + "," + rightInvRootStr + ")";
			}
			else
			{
				generatedCode = holderCode + "=std::pow(" + holderCode + ",1.0/" + exprCode + ")";
			}
		}
		else
		{
			generatedCode = holderCode + pNode->token.value + exprCode;
		}
	}

	void CXXCodegen::Visit(ASTNodeVar* pNode)
	{
		generatedCode = pNode->token.value;
	}

	void CXXCodegen::Visit(ASTNodeLog* pNode)
	{
		pNode->pExression->Accept(this);
		generatedCode = "std::cout<<" + generatedCode;
	}

	void CXXCodegen::Visit(ASTNodeIfStatement* pNode)
	{
		pNode->pExpression->Accept(this);
		std::string exprCode = generatedCode;

		pNode->pIfScope->Accept(this);
		std::string ifScopeCode = generatedCode;
		std::string tempCode = "";

		if (pNode->bComptimeEval) // generate 'comptime if'
		{
			if (!pCompilerUtils->IsBoolean(exprCode))
			{
				std::cout << "CXXError: Expression cannot be evaluated at compile time.\n\n";
			}
			else if (pCompilerUtils->StringToBoolean(exprCode))
			{
				tempCode += ifScopeCode;
			}
			else if (pNode->bHasElseScope)
			{
				pNode->pElseScope->Accept(this);
				tempCode += generatedCode;
			}
		}
		else // genereate runtime 'if'
		{
			tempCode = "if(" + exprCode + "){\n" + ifScopeCode + "}";

			if (pNode->bHasElseScope)
			{
				pNode->pElseScope->Accept(this);
				tempCode += "else{\n" + generatedCode + "}";
			}
		}

		generatedCode = tempCode;
	}

	void CXXCodegen::Visit(ASTNodeEmptyStatement* pNode)
	{
	}

	void CXXCodegen::Visit(ASTNodeFun* pNode)
	{
		pNode->pScope->Accept(this);
		const std::string returnType = pCXXCompilerUtils->ToPrimitive(pNode->pReturType->token.value);
		generatedCode = "\n" + returnType + " " + pNode->name + "()\n{\n" + generatedCode + "}";
	}

	void CXXCodegen::Visit(ASTNodeFunParamDeclStatement* pNode)
	{
	}

	const std::string& CXXCodegen::GetGeneratedCode() const noexcept
	{
		return generatedCode;
	}
}