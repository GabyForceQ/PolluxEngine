/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "ParseContext.hpp"
#include "AST/ASTFWD.hpp"
#include "Scope/ScopeKindFlag.hpp"

#include "PxTypes.hpp"

namespace Pollux::Lang
{
	class Lexer;
	class PxSymbolParser;

	class Parser final
	{
	public:
		explicit Parser(Lexer* pScanner) noexcept;

		ASTNodeBase* Parse();

		ASTNodeScope* ParseUnit();

		std::deque<ASTNodeBase*> ParseScopeStatements();

		ASTNodeScope* ParseScope();

		/*ASTNodeDeclStatement* ParseDeclStatement(const ParseContext* pContext);
		
		ASTNodeDeclHolder* ParseDeclHolder(const ParseContext* pContext);
		
		ASTNodeType* ParseType(const ParseContext* pContext);
		
		ASTNodeScope* ParseUnit(const ParseContext* pContext);
		
		ASTNodeScope* ParseScope(const ParseContext* pContext);
		
		ASTNodeScope* ParseGlobalScope(const ParseContext* pContext);

		std::deque<ASTNodeBase*> ParseFunStatementList(const ParseContext* pContext);

		std::deque<ASTNodeBase*> ParseGlobalStatementList(const ParseContext* pContext);
		
		ASTNodeBase* ParseFunStatement(const ParseContext* pContext);

		ASTNodeBase* ParseGlobalStatement(const ParseContext* pContext);
		
		ASTNodeAssign* ParseAssignment(const ParseContext* pContext);
		
		ASTNodeVar* ParseVar(const ParseContext* pContext);
		
		ASTNodeExpression* ParseExpression(const ParseContext* pContext);
		
		ASTNodeEmptyStatement* ParseEmptyStatement(const ParseContext* pContext);
		
		ASTNodeLog* ParseLogStatement(const ParseContext* pContext);
		
		ASTNodeIfStatement* ParseIfStatement(const ParseContext* pContext);
		
		ASTNodeFun* ParseFun(const ParseContext* pContext);
		
		ASTNodeReturn* ParseReturnStatement(const ParseContext* pContext);*/

		Token* PeekToken(size_t i = 0_sz);

		Token* EatToken();

		Token* EatToken(TokenKind kind);

		Token* EatTokenOverEOLs();

		std::pair<Token*, bool> ExpectToken(TokenKind kind);

		void PutBackToken();

		PxSymbolTable* m_pUnitSymbolTable = nullptr;

	private:
		//bool EndOfStatement();
		//void SkipEndOfStatement();

		std::deque<std::function<bool()>> binopPrecedence = {};
		Lexer* pScanner = nullptr;
		ParseContext* m_pContext;

		friend PxSymbolParser;
	};
}