/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Parser.hpp"
#include "Tokenizer/Lexer.hpp"
#include "AST/ASTNodes.hpp"

namespace Pollux::Lang
{
    Parser::Parser(Lexer* pScanner) noexcept
        :
        pScanner{ pScanner },
        currentToken{ pScanner->NextToken() }
    {
        // Priority 0: ** //
        binopPrecedence.push_back([&]() -> bool
        {
            return currentToken.kind == TokenKind::OperatorPow ||
                currentToken.kind == TokenKind::OperatorRoot;
        });

        // Priority 1: * / %
        binopPrecedence.push_back([&]() -> bool
        {
            return currentToken.kind == TokenKind::OperatorMul ||
                currentToken.kind == TokenKind::OperatorDiv ||
                currentToken.kind == TokenKind::OperatorMod;
        });

        // Priority 2: + -
        binopPrecedence.push_back([&]() -> bool
        {
            return currentToken.kind == TokenKind::OperatorAdd ||
                currentToken.kind == TokenKind::OperatorSub;
        });

        // Priority 3: < <= > >=
        binopPrecedence.push_back([&]() -> bool
        {
            return currentToken.kind == TokenKind::OperatorLe ||
                currentToken.kind == TokenKind::OperatorLt ||
                currentToken.kind == TokenKind::OperatorGe ||
                currentToken.kind == TokenKind::OperatorGt;
        });

        // Priority 4: == !=
        binopPrecedence.push_back([&]() -> bool
        {
            return currentToken.kind == TokenKind::OperatorEq ||
                currentToken.kind == TokenKind::OperatorNe;
        });

        // Priority 5: &&
        binopPrecedence.push_back([&]() -> bool
        {
            return currentToken.kind == TokenKind::LogicalAnd;
        });

        // Priority 6: ||
        binopPrecedence.push_back([&]() -> bool
        {
            return currentToken.kind == TokenKind::LogicalOr;
        });
    }

    void Parser::FastEat()
    {
        currentToken = pScanner->NextToken();
    }

    void Parser::Eat()
    {
        SkipEndOfStatement();
        currentToken = pScanner->NextToken();
        SkipEndOfStatement();
    }
    
    bool Parser::Eat(TokenKind tokenKind)
    {
        SkipEndOfStatement();

        if (currentToken.kind == tokenKind)
        {
            currentToken = pScanner->NextToken();
            SkipEndOfStatement();
            return true;
        }

        return false;
    }
    
    ASTNodeDeclStatement* Parser::ParseDeclStatement(bool bConstant)
    {
        Eat(currentToken.kind);

        std::deque pDeclHolders =
        {
            ParseDeclHolder(bConstant)
        };

        Eat(TokenKind::Identifier);

        while (currentToken.kind == TokenKind::Comma)
        {
            Eat(TokenKind::Comma);

            pDeclHolders.push_back(ParseDeclHolder(bConstant));
        }

        return new ASTNodeDeclStatement(pDeclHolders, bConstant);
    }
    
    ASTNodeDeclHolder* Parser::ParseDeclHolder(bool bConstant)
    {
        auto pNode = new ASTNodeDeclHolder();
        pNode->bComptimeEval = bConstant;

        Token tok_id = currentToken;
        Eat(TokenKind::Identifier);

        if (currentToken.kind == TokenKind::Colon)
        {
            Eat(currentToken.kind);

            pNode->bAutoDeduction = false;
            pNode->pType = ParseType();
        }

        pNode->pAssignment = new ASTNodeAssign(tok_id);
        pNode->pAssignment->pHolder = new ASTNodeVar(tok_id);
        
        Eat(TokenKind::Identifier);
        Eat(TokenKind::OperatorAssign);
        
        pNode->pAssignment->pExpression = ParseExpression();
        return pNode;
    }
    
    ASTNodeType* Parser::ParseType()
    {
        if (currentToken.kind != TokenKind::Identifier)
        {
            // todo. error
        }

        return new ASTNodeType(currentToken);
    }
    
    ASTNodeScope* Parser::ParseUnit()
    {
        if (!Eat(TokenKind::KeywordUnit))
        {
            std::cout << "parser error: unit expected\n";
        }
        else
        {
            Eat(TokenKind::Identifier);
        }

        ASTNodeScope* pNode = ParseGlobalScope();
        
        return pNode;
    }
    
    ASTNodeScope* Parser::ParseScope(const ScopeKindFlag scopeKindFlag)
    {
        Eat(TokenKind::OpenBrace);

        std::deque<ASTNodeBase*> pStatements = ParseFunStatementList();

        Eat(TokenKind::CloseBrace);

        ASTNodeScope* pNode = new ASTNodeScope();
        pNode->kindFlag |= scopeKindFlag;

        for (ASTNodeBase* pStatement : pStatements)
        {
            pNode->InsertStatement(pStatement);
        }

        return pNode;
    }

    ASTNodeScope* Parser::ParseGlobalScope()
    {
        std::deque<ASTNodeBase*> pStatements = ParseGlobalStatementList();

        ASTNodeScope* pNode = new ASTNodeScope();

        for (ASTNodeBase* pStatement : pStatements)
        {
            pNode->InsertStatement(pStatement);
        }

        return pNode;
    }
   
    std::deque<ASTNodeBase*> Parser::ParseFunStatementList()
    {
        std::deque<ASTNodeBase*> pNodeList;

        if (currentToken.kind != TokenKind::CloseBrace)
        {
            if (currentToken.kind == TokenKind::OpenBrace)
            {
                ASTNodeScope* pScope = ParseScope(ScopeKindFlag::Fun);
            }

            if (currentToken.kind != TokenKind::CloseBrace)
            {
                ASTNodeBase* pStatement = ParseFunStatement();
                pNodeList = { pStatement };

                while (currentToken.kind != TokenKind::CloseBrace)
                {
                    pNodeList.push_back(ParseFunStatement());
                }

                if (currentToken.kind == TokenKind::Identifier)
                {
                    throw std::runtime_error(""); //////
                }
            }
        }

        return pNodeList;
    }

    std::deque<ASTNodeBase*> Parser::ParseGlobalStatementList()
    {
        std::deque<ASTNodeBase*> pNodeList;

        if (currentToken.kind != TokenKind::Eof)
        {
            ASTNodeBase* pStatement = ParseGlobalStatement();
            pNodeList = { pStatement };

            while ((currentToken.kind != TokenKind::Eof))
            {
                pNodeList.push_back(ParseGlobalStatement());
            }
        }

        return pNodeList;
    }
    
    ASTNodeBase* Parser::ParseFunStatement()
    {
        ASTNodeBase* pNode = nullptr;

        switch (currentToken.kind)
        {
        case TokenKind::KeywordVar:
        {
            pNode = ParseDeclStatement(false);
            break;
        }
        case TokenKind::KeywordVal:
        {
            pNode = ParseDeclStatement(true);
            break;
        }
        case TokenKind::Identifier:
        {
            pNode = ParseAssignment();
            break;
        }
        case TokenKind::KeywordLog:
        {
            pNode = ParseLogStatement(false);
            break;
        }
        case TokenKind::KeywordIf:
        {
            pNode = ParseIfStatement(false);
            break;
        }
        case TokenKind::KeywordReturn:
        {
            pNode = ParseReturnStatement();
            break;
        }
        case TokenKind::KeywordComptime:
        {
            FastEat();

            switch (currentToken.kind)
            {
            case TokenKind::KeywordLog:
            {
                pNode = ParseLogStatement(true);
                break;
            }
            case TokenKind::KeywordVar:
            {
                pNode = ParseDeclStatement(true);
                break;
            }
            case TokenKind::KeywordVal:
            {
                pNode = ParseDeclStatement(true);
                break;
            }
            case TokenKind::KeywordIf:
            {
                pNode = ParseIfStatement(true);
                break;
            }
            default: break;
            }

            break;
        }
        default:
        {
            pNode = ParseEmptyStatement();
            break;
        }
        }
        
        return pNode;
    }

    ASTNodeBase* Parser::ParseGlobalStatement()
    {
        ASTNodeBase* pNode = nullptr;

        switch (currentToken.kind)
        {
        case TokenKind::KeywordVar:
        {
            pNode = ParseDeclStatement(false);
            break;
        }
        case TokenKind::KeywordVal:
        {
            pNode = ParseDeclStatement(true);
            break;
        }
        case TokenKind::KeywordFun:
        {
            pNode = ParseFun();
            break;
        }
        default:
        {
            pNode = ParseEmptyStatement();
            break;
        }
        case TokenKind::KeywordComptime:
        {
            FastEat();

            switch (currentToken.kind)
            {
            case TokenKind::KeywordLog:
            {
                pNode = ParseLogStatement(true);
                break;
            }
            case TokenKind::KeywordVar:
            {
                pNode = ParseDeclStatement(true);
                break;
            }
            case TokenKind::KeywordVal:
            {
                pNode = ParseDeclStatement(true);
                break;
            }
            case TokenKind::KeywordIf:
            {
                pNode = ParseIfStatement(true);
                break;
            }
            default: break;
            }

            break;
        }
        }

        return pNode;
    }
   
    ASTNodeAssign* Parser::ParseAssignment()
    {
        ASTNodeAssign* pNode = new ASTNodeAssign(currentToken); //////
        pNode->pHolder = ParseVar();
        pNode->token = currentToken;

        switch (currentToken.kind)
        {
        case TokenKind::OperatorAssign:
        case TokenKind::OperatorAddAssign:
        case TokenKind::OperatorSubAssign:
        case TokenKind::OperatorMulAssign:
        case TokenKind::OperatorDivAssign:
        case TokenKind::OperatorModAssign:
        case TokenKind::OperatorPowAssign:
        case TokenKind::OperatorRootAssign:
        case TokenKind::LogicalAnd:
        case TokenKind::LogicalOr:
        {
            FastEat();
            break;
        }
        default: break;
        }

        pNode->pExpression = ParseExpression();
        return pNode;
    }
    
    ASTNodeVar* Parser::ParseVar()
    {
        ASTNodeVar* pNode = new ASTNodeVar(currentToken);
        pNode->token = currentToken; // todo. useless
        
        Eat(TokenKind::Identifier);
        
        return pNode;
    }
    
    ASTNodeExpression* Parser::ParseExpression()
    {
        using BasicExprFun = std::function<ASTNodeExpression*(int32_t priority)>;

        BasicExprFun ParseUnop = [&](int32_t priority) -> ASTNodeExpression*
        {
            Token token = currentToken;

            switch (token.kind)
            {
            case TokenKind::OperatorAdd:
            case TokenKind::OperatorSub:
            case TokenKind::LogicalNot:
            {
                ASTNodeExpression* pNode = new ASTNodeExpression(ExpressionKind::Unary);
                pNode->token = currentToken;
                
                Eat(token.kind);
                
                pNode->pUnaryOp = ParseUnop(priority);
                return pNode;
            }
            default: break;
            }

            switch (token.kind)
            {
            case TokenKind::LiteralInteger:
            case TokenKind::LiteralFloat:
            case TokenKind::LiteralDouble:
            case TokenKind::KeywordTrue:
            case TokenKind::KeywordFalse:
            {
                ASTNodeExpression* pNode = new ASTNodeExpression(ExpressionKind::NumberLiteral);
                pNode->token = currentToken;
                
                Eat(token.kind);
                
                return pNode;
            }
            default: break;
            }

            if (token.kind == TokenKind::LiteralString)
            {
                ASTNodeExpression* pNode = new ASTNodeExpression(ExpressionKind::StringLiteral);
                pNode->token = currentToken;
                
                Eat(token.kind);
                
                return pNode;
            }

            if (token.kind == TokenKind::OpenParen)
            {
                Eat(TokenKind::OpenParen);
                
                ASTNodeExpression* pNode = ParseExpression();
                
                Eat(TokenKind::CloseParen);
                
                return pNode;
            }

            if (token.kind == TokenKind::Identifier)
            {
                ASTNodeExpression* pNode = new ASTNodeExpression(ExpressionKind::DynamicHolder);
                pNode->token = currentToken;
                
                Eat(token.kind);
                
                return pNode;
            }

            throw std::runtime_error("");
        };

        BasicExprFun ParseBinop = [&](int32_t priority) -> ASTNodeExpression*
        {
            auto pNode = (priority > 0 ? ParseBinop(priority - 1) : ParseUnop(priority));

            while (binopPrecedence[priority]())
            {
                Token tokenOperator = currentToken;
                Eat(currentToken.kind);

                ASTNodeExpression* pTempNode = new ASTNodeExpression(ExpressionKind::Binary);
                pTempNode->token = tokenOperator;
                pTempNode->pBinaryOpLeft = pNode;
                pTempNode->pBinaryOpRight = (priority > 0 ? ParseBinop(priority - 1) : ParseUnop(priority));

                pNode = pTempNode;
            }

            return pNode;
        };

        return ParseBinop(static_cast<int32_t>(binopPrecedence.size()) - 1);
    }
    
    ASTNodeEmptyStatement* Parser::ParseEmptyStatement()
    {
        return new ASTNodeEmptyStatement();
    }
    
    ASTNodeLog* Parser::ParseLogStatement(bool bComptimeEval)
    {
        FastEat();

        ASTNodeLog* pNode = new ASTNodeLog();
        pNode->pExression = ParseExpression();
        pNode->bComptimeEval = bComptimeEval;

        return pNode;
    }
    
    ASTNodeIfStatement* Parser::ParseIfStatement(bool bComptimeEval)
    {
        FastEat();

        ASTNodeIfStatement* pNode = new ASTNodeIfStatement();
        pNode->bComptimeEval = bComptimeEval;
        pNode->pExpression = ParseExpression();
        pNode->pIfScope = ParseScope(ScopeKindFlag::IfElse);

        while (Eat(TokenKind::KeywordElse))
        {
            if (bComptimeEval)
            {
                if (currentToken.kind == TokenKind::KeywordComptime)
                {
                    FastEat();
                    Eat(TokenKind::KeywordIf);

                    ASTNodeExpression* pExpression = ParseExpression();
                    ASTNodeScope* pElseIfScope = ParseScope(ScopeKindFlag::IfElse);
                    pNode->pElseIfScopes[pElseIfScope] = pExpression;
                }
                else
                {
                    pNode->pElseScope = ParseScope(ScopeKindFlag::IfElse);
                    break;
                }
            }
            else
            {
                if (currentToken.kind == TokenKind::KeywordIf)
                {
                    FastEat();

                    ASTNodeExpression* pExpression = ParseExpression();
                    ASTNodeScope* pElseIfScope = ParseScope(ScopeKindFlag::IfElse);
                    pNode->pElseIfScopes[pElseIfScope] = pExpression;
                }
                else
                {
                    pNode->pElseScope = ParseScope(ScopeKindFlag::IfElse);
                    break;
                }
            }
        }

        return pNode;
    }
    
    ASTNodeFun* Parser::ParseFun()
    {
        FastEat();

        ASTNodeFun* pNode = new ASTNodeFun();
        pNode->name = currentToken.value;

        if (!Eat(TokenKind::Identifier))
        {
            throw std::runtime_error("Expected: identifier.");
        }
        else
        {
            if (!Eat(TokenKind::OpenParen))
            {
                throw std::runtime_error("Expected: '('");
            }
            else
            {
                //ASTNodeFunParamDeclStatement* pParams = new ASTNodeFunParamDeclStatement();

                if (!Eat(TokenKind::CloseParen))
                {
                    throw std::runtime_error("Expected: ')'");
                }
                else
                {
                    if (currentToken.kind == TokenKind::Colon)
                    {
                        FastEat(); // eat ':'

                        pNode->pReturnType = ParseType();
                        
                        Eat(currentToken.kind);
                        
                        //if (!Eat(currentToken.kind)) ////
                        //	throw std::runtime_error("Expected: identifier.");
                    }

                    pNode->pScope = ParseScope(ScopeKindFlag::Fun);
                }
            }
        }

        return pNode;
    }

    ASTNodeReturn* Parser::ParseReturnStatement()
    {
        ASTNodeReturn* pNode = new ASTNodeReturn();
        FastEat(); // eat 'return' keyword

        pNode->pExpression = ParseExpression();
        //pNode->pReturnType = pNode->pExpression->pBinaryOpType; //?
        //pNode->pFunction = pContext->pFunction;

        return pNode;
    }
    
    ASTNodeBase* Parser::Parse()
    {
        ASTNodeScope* pScope = ParseUnit();

        if (currentToken.kind != TokenKind::Eof)
        {
            throw std::runtime_error("NOT EOF");
        }

        return pScope;
    }
    
    const Token& Parser::GetCurrentToken() const noexcept
    {
        return currentToken;
    }

    bool Parser::EndOfStatement()
    {
        return currentToken.kind == TokenKind::Semicolon || currentToken.kind == TokenKind::Eol;
    }

    void Parser::SkipEndOfStatement()
    {
        while (currentToken.kind == TokenKind::Eol)
        {
            currentToken = pScanner->NextToken();
        }
    }
}