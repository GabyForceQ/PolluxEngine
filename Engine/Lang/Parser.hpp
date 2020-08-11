/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "Tokenizer/Token.hpp"
#include "AST/ASTFWD.hpp"
#include "Scope/ScopeKindFlag.hpp"

namespace Pollux::Lang
{
	class Lexer;

	class Parser final
	{
	public:
		explicit Parser(Lexer* pScanner) noexcept;

		void FastEat();

		void Eat();

		bool Eat(TokenKind tokenKind);

		ASTNodeDeclStatement* ParseDeclStatement(bool bConstant);
		
		ASTNodeDeclHolder* ParseDeclHolder(bool bConstant);
		
		ASTNodeType* ParseType();
		
		ASTNodeScope* ParseUnit();
		
		ASTNodeScope* ParseScope(const ScopeKindFlag scopeKindFlag);
		
		ASTNodeScope* ParseGlobalScope();

		std::deque<ASTNodeBase*> ParseFunStatementList();

		std::deque<ASTNodeBase*> ParseGlobalStatementList();
		
		ASTNodeBase* ParseFunStatement();

		ASTNodeBase* ParseGlobalStatement();
		
		ASTNodeAssign* ParseAssignment();
		
		ASTNodeVar* ParseVar();
		
		ASTNodeExpression* ParseExpression();
		
		ASTNodeEmptyStatement* ParseEmptyStatement();
		
		ASTNodeLog* ParseLogStatement(bool bComptimeEval);
		
		ASTNodeIfStatement* ParseIfStatement(bool bComptimeEval);
		
		ASTNodeFun* ParseFun();
		
		ASTNodeReturn* ParseReturnStatement();

		ASTNodeBase* Parse();

		const Token& GetCurrentToken() const noexcept;

	private:
		bool EndOfStatement();
		void SkipEndOfStatement();

		std::deque<std::function<bool()>> binopPrecedence = {};
		Lexer* pScanner = nullptr;
		Token currentToken;
	};
}