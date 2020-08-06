/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "Tokenizer/Token.hpp"
#include "AST/ASTFWD.hpp"

namespace Pollux::Lang
{
	class Lexer;

	class Parser final
	{
	public:
		explicit Parser(Lexer* pScanner) noexcept;

		void Eat();

		bool Eat(TokenKind tokenKind);

		ASTNodeDeclStatement* ParseDeclStatement(bool bConstant);
		
		ASTNodeDeclHolder* ParseDeclHolder(bool bConstant);
		
		ASTNodeType* ParseType();
		
		ASTNodeScope* ParsePackage();
		
		ASTNodeScope* ParseScope();
		
		std::deque<ASTNodeBase*> ParseStatementList();
		
		ASTNodeBase* ParseStatement();
		
		ASTNodeAssign* ParseAssignment();
		
		ASTNodeVar* ParseVar();
		
		ASTNodeExpression* ParseExpression();
		
		ASTNodeEmptyStatement* ParseEmptyStatement();
		
		ASTNodeLog* ParseLog();
		
		ASTNodeIfStatement* ParseIfStatement(bool bComptimeEval);
		
		ASTNodeFun* ParseFun();
		
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