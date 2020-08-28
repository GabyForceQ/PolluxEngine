/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Parser.hpp"
#include "ProtoParser.hpp"
#include "Tokenizer/Lexer.hpp"
#include "AST/ASTNodes.hpp"

namespace Pollux::Lang
{
    Parser::Parser(Lexer* pScanner) noexcept
        :
        pScanner{ pScanner },
        m_pContext{ new ParseContext() }
    {
        // Lex the unit file
        {
            size_t i = 0_sz;

            while (true)
            {
                Token token = pScanner->NextToken();

                if (token.kind == TokenKind::Eof)
                {
                    break; // finish when end of file is reached
                }

                if (i != 0_sz && token.kind == TokenKind::Eol && token.kind == m_pContext->m_Tokens[i - 1].kind)
                {
                    continue; // skip successive end of lines
                }
                else
                {
                    m_pContext->m_Tokens.push_back(token);
                }

                i++;
            }

            m_pContext->m_TokenCount = m_pContext->m_Tokens.size();
        }

        // Priority 0: ** //
        /*binopPrecedence.push_back([&]() -> bool
        {
            return m_Context.m_CurrentToken.kind == TokenKind::OperatorPow ||
                m_Context.m_CurrentToken.kind == TokenKind::OperatorRoot;
        });

        // Priority 1: * / %
        binopPrecedence.push_back([&]() -> bool
        {
            return m_Context.m_CurrentToken.kind == TokenKind::OperatorMul ||
                m_Context.m_CurrentToken.kind == TokenKind::OperatorDiv ||
                m_Context.m_CurrentToken.kind == TokenKind::OperatorMod;
        });

        // Priority 2: + -
        binopPrecedence.push_back([&]() -> bool
        {
            return m_Context.m_CurrentToken.kind == TokenKind::OperatorAdd ||
                m_Context.m_CurrentToken.kind == TokenKind::OperatorSub;
        });

        // Priority 3: < <= > >=
        binopPrecedence.push_back([&]() -> bool
        {
            return m_Context.m_CurrentToken.kind == TokenKind::OperatorLe ||
                m_Context.m_CurrentToken.kind == TokenKind::OperatorLt ||
                m_Context.m_CurrentToken.kind == TokenKind::OperatorGe ||
                m_Context.m_CurrentToken.kind == TokenKind::OperatorGt;
        });

        // Priority 4: == !=
        binopPrecedence.push_back([&]() -> bool
        {
            return m_Context.m_CurrentToken.kind == TokenKind::OperatorEq ||
                m_Context.m_CurrentToken.kind == TokenKind::OperatorNe;
        });

        // Priority 5: &&
        binopPrecedence.push_back([&]() -> bool
        {
            return m_Context.m_CurrentToken.kind == TokenKind::LogicalAnd;
        });

        // Priority 6: ||
        binopPrecedence.push_back([&]() -> bool
        {
            return m_Context.m_CurrentToken.kind == TokenKind::LogicalOr;
        });*/
    }

    ASTNodeBase* Parser::Parse()
    {
        ASTNodeScope* pScope = ParseUnit();

        //if (pToken->kind != TokenKind::Eof)
        //{
        //    throw std::runtime_error("NOT EOF");
        //}

        return pScope;
    }

    ASTNodeScope* Parser::ParseUnit()
    {
        Token* pToken = PeekToken();


        // todo. check package name
        pToken = EatToken();
        pToken = EatToken();


        m_pUnitSymbolTable = (new PxSymbolParser(this))->ParseScopeMembers();

        if (m_pContext->m_CurrentTokenIndex != m_pContext->m_Tokens.size() - 1)
        {
            //InvalidTokenError(PeekToken());
        }

        ASTNodeScope* pNode = ParseScope();
        //pNode-

        return pNode;
    }

    std::deque<ASTNodeBase*> Parser::ParseScopeStatements()
    {
        std::deque<ASTNodeBase*> pNodeList;

        //if (m_pContext->m_CurrentToken.kind != TokenKind::Eof)
        //{
        //    ASTNodeBase* pStatement = ParseGlobalStatement(pContext);
        //    pNodeList = { pStatement };
        //
        //    while ((pContext->m_CurrentToken.kind != TokenKind::Eof))
        //    {
        //        pNodeList.push_back(ParseGlobalStatement(pContext));
        //    }
        //}

        return pNodeList;
    }

    ASTNodeScope* Parser::ParseScope()
    {
        ASTNodeScope* pNode = new ASTNodeScope();

        switch (m_pContext->m_Scope.m_Kind)
        {
        case PxScopeKind::Global:
        {
            break;
        }
        case PxScopeKind::Fun:
        {
            break;
        }
        case PxScopeKind::Struct:
        {
            break;
        }
        default: break;
        }

        return pNode;
    }

    //void Parser::Eat()
    //{
    //    SkipEndOfStatement();
    //    m_Context.m_CurrentToken = m_Context.m_Tokens[++m_Context.m_TokenIndex];
    //    SkipEndOfStatement();
    //}
    //
    //bool Parser::Eat(TokenKind tokenKind)
    //{
    //    SkipEndOfStatement();
    //
    //    if (m_Context.m_CurrentToken.kind == tokenKind)
    //    {
    //        m_Context.m_CurrentToken = m_Context.m_Tokens[++m_Context.m_TokenIndex];
    //        SkipEndOfStatement();
    //        return true;
    //    }
    //
    //    return false;
    //}
    
    /*ASTNodeDeclStatement* Parser::ParseDeclStatement(const ParseContext* pContext)
    {
        Eat(m_Context.m_CurrentToken.kind);

        std::deque pDeclHolders =
        {
            ParseDeclHolder(pContext)
        };

        while (m_Context.m_CurrentToken.kind == TokenKind::Comma)
        {
            Eat(TokenKind::Comma);

            pDeclHolders.push_back(ParseDeclHolder(pContext));
        }

        return new ASTNodeDeclStatement(pDeclHolders, pContext->m_bConstant);
    }
    
    ASTNodeDeclHolder* Parser::ParseDeclHolder(const ParseContext* pContext)
    {
        auto pNode = new ASTNodeDeclHolder();
        pNode->bConstant = pContext->m_bConstant;
        pNode->bComptimeEval = pContext->m_bComptimeEval;

        Token tok_id = pContext->m_CurrentToken;
        Eat(TokenKind::Identifier);

        if (pContext->m_CurrentToken.kind == TokenKind::Colon)
        {
            Eat(pContext->m_CurrentToken.kind);

            pNode->bAutoDeduction = false;
            pNode->pType = ParseType(pContext);
        }

        pNode->pAssignment = new ASTNodeAssign();
        pNode->pAssignment->pHolder = new ASTNodeVar(tok_id);
        pNode->pAssignment->token = tok_id;
        
        Eat(TokenKind::Identifier);
        Eat(TokenKind::OperatorAssign);
        
        pNode->pAssignment->pExpression = ParseExpression(pContext);
        return pNode;
    }
    
    ASTNodeType* Parser::ParseType(const ParseContext* pContext)
    {
        if (pContext->m_CurrentToken.kind != TokenKind::Identifier)
        {
            // todo. error
        }

        return new ASTNodeType(pContext->m_CurrentToken);
    }
    
    ASTNodeScope* Parser::ParseUnit(const ParseContext* pContext)
    {
        if (!Eat(TokenKind::KeywordUnit))
        {
            std::cout << "parser error: unit expected\n";
        }
        else
        {
            Eat(TokenKind::Identifier);
        }

        ASTNodeScope* pNode = ParseGlobalScope(pContext);
        
        return pNode;
    }
    
    ASTNodeScope* Parser::ParseScope(const ParseContext* pContext)
    {
        Eat(TokenKind::OpenBrace);

        std::deque<ASTNodeBase*> pStatements = ParseFunStatementList(pContext);

        Eat(TokenKind::CloseBrace);

        ASTNodeScope* pNode = new ASTNodeScope();
        pNode->kindFlag |= pContext->m_ScopeKindFlag;

        for (ASTNodeBase* pStatement : pStatements)
        {
            pNode->InsertStatement(pStatement);
        }

        return pNode;
    }

    ASTNodeScope* Parser::ParseGlobalScope(const ParseContext* pContext)
    {
        std::deque<ASTNodeBase*> pStatements = ParseGlobalStatementList(pContext);

        ASTNodeScope* pNode = new ASTNodeScope();

        for (ASTNodeBase* pStatement : pStatements)
        {
            pNode->InsertStatement(pStatement);
        }

        return pNode;
    }
   
    std::deque<ASTNodeBase*> Parser::ParseFunStatementList(const ParseContext* pContext)
    {
        std::deque<ASTNodeBase*> pNodeList;

        if (pContext->m_CurrentToken.kind != TokenKind::CloseBrace)
        {
            if (pContext->m_CurrentToken.kind == TokenKind::OpenBrace)
            {
                ParseContext context{ pContext };
                context.m_ScopeKindFlag |= ScopeKindFlag::Fun;

                ASTNodeScope* pScope = ParseScope(&context);
            }

            if (pContext->m_CurrentToken.kind != TokenKind::CloseBrace)
            {
                ASTNodeBase* pStatement = ParseFunStatement(pContext);
                pNodeList = { pStatement };

                while (pContext->m_CurrentToken.kind != TokenKind::CloseBrace)
                {
                    pNodeList.push_back(ParseFunStatement(pContext));
                }

                if (pContext->m_CurrentToken.kind == TokenKind::Identifier)
                {
                    throw std::runtime_error(""); //////
                }
            }
        }

        return pNodeList;
    }

    std::deque<ASTNodeBase*> Parser::ParseGlobalStatementList(const ParseContext* pContext)
    {
        std::deque<ASTNodeBase*> pNodeList;

        if (pContext->m_CurrentToken.kind != TokenKind::Eof)
        {
            ASTNodeBase* pStatement = ParseGlobalStatement(pContext);
            pNodeList = { pStatement };

            while ((pContext->m_CurrentToken.kind != TokenKind::Eof))
            {
                pNodeList.push_back(ParseGlobalStatement(pContext));
            }
        }

        return pNodeList;
    }
    
    ASTNodeBase* Parser::ParseFunStatement(const ParseContext* pContext)
    {
        ASTNodeBase* pNode = nullptr;

        switch (pContext->m_CurrentToken.kind)
        {
        case TokenKind::KeywordVar:
        {
            ParseContext context{ pContext };
            context.m_bConstant = false;

            pNode = ParseDeclStatement(&context);
            break;
        }
        case TokenKind::KeywordVal:
        {
            ParseContext context{ pContext };
            context.m_bConstant = true;

            pNode = ParseDeclStatement(&context);
            break;
        }
        case TokenKind::Identifier:
        {
            ParseContext context{ pContext };
            //context.m_PreviusToken = pContext->m_CurrentToken;

            Eat();

            switch (pContext->m_CurrentToken.kind)
            {
            case TokenKind::OpenParen:
            {
                pNode = ParseExpression(&context);
                break;
            }
            case TokenKind::OperatorAssign:
            {
                pNode = ParseAssignment(&context);
                break;
            }
            default: break;
            }

            break;
        }
        case TokenKind::KeywordLog:
        {
            pNode = ParseLogStatement(pContext);
            break;
        }
        case TokenKind::KeywordIf:
        {
            pNode = ParseIfStatement(pContext);
            break;
        }
        case TokenKind::KeywordReturn:
        {
            pNode = ParseReturnStatement(pContext);
            break;
        }
        case TokenKind::KeywordComptime:
        {
            Eat();

            ParseContext context{ pContext };
            context.m_bComptimeEval = true;

            switch (pContext->m_CurrentToken.kind)
            {
            case TokenKind::KeywordLog:
            {
                pNode = ParseLogStatement(&context);
                break;
            }
            case TokenKind::KeywordVar:
            {
                context.m_bConstant = false;

                pNode = ParseDeclStatement(&context);
                break;
            }
            case TokenKind::KeywordVal:
            {
                context.m_bConstant = false;

                pNode = ParseDeclStatement(&context);
                break;
            }
            case TokenKind::KeywordIf:
            {
                pNode = ParseIfStatement(&context);
                break;
            }
            default: break;
            }

            break;
        }
        default:
        {
            pNode = ParseEmptyStatement(pContext);
            break;
        }
        }
        
        return pNode;
    }

    ASTNodeBase* Parser::ParseGlobalStatement(const ParseContext* pContext)
    {
        ASTNodeBase* pNode = nullptr;

        switch (pContext->m_CurrentToken.kind)
        {
        case TokenKind::KeywordVar:
        {
            ParseContext context{ pContext };
            context.m_bConstant = false;

            pNode = ParseDeclStatement(&context);
            break;
        }
        case TokenKind::KeywordVal:
        {
            ParseContext context{ pContext };
            context.m_bConstant = true;

            pNode = ParseDeclStatement(&context);
            break;
        }
        case TokenKind::KeywordFun:
        {
            pNode = ParseFun(pContext);
            break;
        }
        default:
        {
            pNode = ParseEmptyStatement(pContext);
            break;
        }
        case TokenKind::KeywordComptime:
        {
            Eat();

            ParseContext context{ pContext };
            context.m_bComptimeEval = true;

            switch (pContext->m_CurrentToken.kind)
            {
            case TokenKind::KeywordLog:
            {
                pNode = ParseLogStatement(&context);
                break;
            }
            case TokenKind::KeywordVar:
            {
                context.m_bConstant = false;

                pNode = ParseDeclStatement(&context);
                break;
            }
            case TokenKind::KeywordVal:
            {
                context.m_bConstant = true;

                pNode = ParseDeclStatement(&context);
                break;
            }
            case TokenKind::KeywordIf:
            {
                pNode = ParseIfStatement(&context);
                break;
            }
            default: break;
            }

            break;
        }
        }

        return pNode;
    }
   
    ASTNodeAssign* Parser::ParseAssignment(const ParseContext* pContext)
    {
        ASTNodeAssign* pNode = new ASTNodeAssign();
        pNode->pHolder = ParseVar(pContext);
        pNode->token = pContext->m_CurrentToken;

        switch (pContext->m_CurrentToken.kind)
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
            Eat();
            break;
        }
        default: break;
        }

        pNode->pExpression = ParseExpression(pContext);
        return pNode;
    }
    
    ASTNodeVar* Parser::ParseVar(const ParseContext* pContext)
    {
        ASTNodeVar* pNode = new ASTNodeVar(pContext->m_CurrentToken);
        pNode->token = pContext->m_CurrentToken; // todo. useless
        
        Eat(TokenKind::Identifier);
        
        return pNode;
    }
    
    ASTNodeExpression* Parser::ParseExpression(const ParseContext* pContext)
    {
        //if (pContext->m_PreviusToken.kind == TokenKind::Identifier)
        {
            //currentToken = pContext->previusToken;
        }

        using BasicExprFun = std::function<ASTNodeExpression*(int32_t priority)>;

        BasicExprFun ParseUnop = [&](int32_t priority) -> ASTNodeExpression*
        {
            Token token = pContext->m_CurrentToken;

            switch (token.kind)
            {
            case TokenKind::OperatorAdd:
            case TokenKind::OperatorSub:
            case TokenKind::LogicalNot:
            {
                ASTNodeExpression* pNode = new ASTNodeExpression(ExpressionKind::Unary);
                pNode->token = pContext->m_CurrentToken;
                
                Eat(token.kind);
                
                pNode->pUnaryOp = ParseUnop(priority);
                return pNode;
            }
            default: break;
            }

            if (token.kind == TokenKind::Identifier) // it can be var/val or function call
            {
                Eat(); // eat identifier

                if (Eat(TokenKind::OpenParen)) // function call '('
                {
                    // todo. function params

                    ASTNodeExpression* pNode = new ASTNodeExpression(ExpressionKind::Unit);
                    pNode->token = token;

                    Eat(TokenKind::CloseParen); // eat ')'

                    return pNode;
                }
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
                pNode->token = pContext->m_CurrentToken;
                
                Eat(token.kind);
                
                return pNode;
            }
            default: break;
            }

            if (token.kind == TokenKind::LiteralString)
            {
                ASTNodeExpression* pNode = new ASTNodeExpression(ExpressionKind::StringLiteral);
                pNode->token = pContext->m_CurrentToken;
                
                Eat(token.kind);
                
                return pNode;
            }

            if (token.kind == TokenKind::OpenParen)
            {
                Eat(TokenKind::OpenParen);
                
                ASTNodeExpression* pNode = ParseExpression(pContext);
                
                Eat(TokenKind::CloseParen);
                
                return pNode;
            }

            if (token.kind == TokenKind::Identifier)
            {
                ASTNodeExpression* pNode = new ASTNodeExpression(ExpressionKind::DynamicHolder);
                pNode->token = pContext->m_CurrentToken;
                
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
                Token tokenOperator = pContext->m_CurrentToken;
                Eat(pContext->m_CurrentToken.kind);

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
    
    ASTNodeEmptyStatement* Parser::ParseEmptyStatement(const ParseContext* pContext)
    {
        return new ASTNodeEmptyStatement();
    }
    
    ASTNodeLog* Parser::ParseLogStatement(const ParseContext* pContext)
    {
        Eat();

        ASTNodeLog* pNode = new ASTNodeLog();
        pNode->pExression = ParseExpression(pContext);
        pNode->bComptimeEval = pContext->m_bComptimeEval;

        return pNode;
    }
    
    ASTNodeIfStatement* Parser::ParseIfStatement(const ParseContext* pContext)
    {
        Eat();

        ParseContext context{ pContext };
        context.m_ScopeKindFlag |= ScopeKindFlag::IfElse;

        ASTNodeIfStatement* pNode = new ASTNodeIfStatement();
        pNode->bComptimeEval = pContext->m_bComptimeEval;
        pNode->pExpression = ParseExpression(pContext);
        pNode->pIfScope = ParseScope(&context);

        while (Eat(TokenKind::KeywordElse))
        {
            if (pContext->m_bComptimeEval)
            {
                if (pContext->m_CurrentToken.kind == TokenKind::KeywordComptime)
                {
                    Eat();
                    Eat(TokenKind::KeywordIf);

                    ASTNodeExpression* pExpression = ParseExpression(&context);
                    ASTNodeScope* pElseIfScope = ParseScope(&context);
                    pNode->pElseIfScopes[pElseIfScope] = pExpression;
                }
                else
                {
                    pNode->pElseScope = ParseScope(&context);
                    break;
                }
            }
            else
            {
                if (pContext->m_CurrentToken.kind == TokenKind::KeywordIf)
                {
                    Eat();

                    ASTNodeExpression* pExpression = ParseExpression(&context);
                    ASTNodeScope* pElseIfScope = ParseScope(&context);
                    pNode->pElseIfScopes[pElseIfScope] = pExpression;
                }
                else
                {
                    pNode->pElseScope = ParseScope(&context);
                    break;
                }
            }
        }

        return pNode;
    }
    
    ASTNodeFun* Parser::ParseFun(const ParseContext* pContext)
    {
        Eat();

        ParseContext context{ pContext };
        context.m_ScopeKindFlag |= ScopeKindFlag::Fun;

        ASTNodeFun* pNode = new ASTNodeFun();
        pNode->name = pContext->m_CurrentToken.value;

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
                    if (pContext->m_CurrentToken.kind == TokenKind::Colon)
                    {
                        Eat(); // eat ':'

                        pNode->pReturnType = ParseType(&context);
                        
                        Eat(pContext->m_CurrentToken.kind);
                        
                        //if (!Eat(currentToken.kind)) ////
                        //	throw std::runtime_error("Expected: identifier.");
                    }

                    pNode->pScope = ParseScope(&context);
                }
            }
        }

        return pNode;
    }

    ASTNodeReturn* Parser::ParseReturnStatement(const ParseContext* pContext)
    {
        ASTNodeReturn* pNode = new ASTNodeReturn();
        Eat(); // eat 'return' keyword

        pNode->pExpression = ParseExpression(pContext);
        //pNode->pReturnType = pNode->pExpression->pBinaryOpType; //?
        //pNode->pFunction = pContext->pFunction;

        return pNode;
    }*/

    Token* Parser::PeekToken(size_t i)
    {
        if (size_t index = m_pContext->m_CurrentTokenIndex + i; index < m_pContext->m_Tokens.size())
        {
            return &m_pContext->m_Tokens.at(index);
        }

        return nullptr;
    }

    Token* Parser::EatToken()
    {
        Token* pToken = PeekToken();
        m_pContext->m_CurrentTokenIndex++;
        return pToken;
    }

    Token* Parser::EatToken(TokenKind kind)
    {
        Token* pToken = PeekToken();

        if (pToken->kind == kind)
        {
            return EatToken();
        }

        return nullptr;
    }

    Token* Pollux::Lang::Parser::EatTokenOverEOLs()
    {
        Token* pToken;

        do
        {
            if (pToken = EatToken(); pToken == nullptr)
            {
                break;
            }
        } while (pToken->kind == TokenKind::Eol);

        return pToken;
    }

    std::pair<Token*, bool> Parser::ExpectToken(TokenKind kind)
    {
        Token* pToken = EatToken();
        bool bCondition = pToken->kind != kind;

        if (bCondition)
        {
            //ASTError(res, "Expected token '" + ToString(pToken->kind) + "', found '%s'", , token_name(pToken->kind));
        }

        return std::make_pair(pToken, !bCondition);
    }

    void Parser::PutBackToken()
    {
        m_pContext->m_CurrentTokenIndex -= 1;
    }

    //bool Parser::EndOfStatement()
    //{
    //    return m_Context.m_CurrentToken.kind == TokenKind::Semicolon ||
    //        m_Context.m_CurrentToken.kind == TokenKind::Eol;
    //}
    //
    //void Parser::SkipEndOfStatement()
    //{
    //    if (m_Context.m_CurrentToken.kind == TokenKind::Eol)
    //    {
    //        m_Context.m_CurrentToken = m_Context.m_Tokens[++m_Context.m_TokenIndex];
    //    }
    //}
}