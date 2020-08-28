/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ProtoParser.hpp"
#include "Parser.hpp"
#include "AST/ASTNodes.hpp"

namespace Pollux::Lang
{
    std::unordered_map<TokenKind, PxUsageKind> defaultUsageMap
    {
        { TokenKind::KeywordVar, PxUsageKind::Anytime },
        { TokenKind::KeywordVal, PxUsageKind::Anytime },
        { TokenKind::KeywordFun, PxUsageKind::Anytime },
        { TokenKind::KeywordStruct, PxUsageKind::Anytime },
        { TokenKind::KeywordEnum, PxUsageKind::Anytime },
        { TokenKind::KeywordLog, PxUsageKind::Runtime }
    };

    PxSymbolParser::PxSymbolParser(Parser* pParser) noexcept
        :
        m_pParser{ pParser },
        m_pContext{ pParser->m_pContext }
    {
    }

    PxSymbolTable* PxSymbolParser::ParseScopeMembers()
    {
        PxSymbolTable* pSymbolTable = new PxSymbolTable();
        pSymbolTable->m_Scope = m_pContext->m_Scope;

        switch (m_pContext->m_Scope.m_Kind)
        {
        case PxScopeKind::Global:
        case PxScopeKind::Struct:
        {
            Token* pToken = m_pParser->EatToken();

            if (pToken == nullptr)
            {
                break;
            }

            uint32_t openBraceCount = 0u;
            bool bEndOfScope = false;

            do
            {
                switch (pToken->kind)
                {
                case TokenKind::OpenBrace: // scope begin
                {
                    openBraceCount++;
                    break;
                }
                case TokenKind::CloseBrace: // scope end
                {
                    if (--openBraceCount == 0u)
                    {
                        bEndOfScope = true;
                    }

                    break;
                }
                case TokenKind::KeywordVar:
                case TokenKind::KeywordVal:
                case TokenKind::KeywordFun:
                case TokenKind::KeywordStruct:
                case TokenKind::KeywordEnum:
                {
                    RegisterSymbol(pSymbolTable, pToken->kind);
                    break;
                }
                case TokenKind::KeywordRuntime:
                case TokenKind::KeywordComptime:
                case TokenKind::KeywordAnytime:
                {
                    ParseUsage(pSymbolTable, pToken->kind);
                    break;
                }
                case TokenKind::KeywordPublic:
                case TokenKind::KeywordPrivate:
                case TokenKind::KeywordProtected:
                case TokenKind::KeywordPackage:
                case TokenKind::KeywordInternal:
                {
                    ParseAccess(pSymbolTable, pToken->kind);
                    break;
                }
                default: break;
                }

                if (pToken = m_pParser->EatToken(); pToken == nullptr)
                {
                    bEndOfScope = true;
                }
            } while (!bEndOfScope);

            break;
        }
        default: break;
        }

        return pSymbolTable;
    }

    void PxSymbolParser::ParseUsage(PxSymbolTable* pSymbolTable, const TokenKind tokenKind)
    {
        TokenKind usageTokenKind = tokenKind;
        Token* pToken = m_pParser->EatTokenOverEOLs();

        if (pToken == nullptr)
        {
            return;
        }

        PxUsageKind currUsageKind = m_pContext->m_Scope.m_Usage.m_Kind;

        switch (usageTokenKind)
        {
        case TokenKind::KeywordRuntime: m_pContext->m_Scope.m_Usage.m_Kind = PxUsageKind::Runtime; break;
        case TokenKind::KeywordComptime: m_pContext->m_Scope.m_Usage.m_Kind = PxUsageKind::Comptime; break;
        case TokenKind::KeywordAnytime: m_pContext->m_Scope.m_Usage.m_Kind = PxUsageKind::Anytime; break;
        default: break;
        }

        BeginSymbol(pSymbolTable, pToken->kind);

        m_pContext->m_Scope.m_Usage.m_Kind = currUsageKind;
    }

    void PxSymbolParser::ParseAccess(PxSymbolTable* pSymbolTable, const TokenKind tokenKind)
    {
        TokenKind accessTokenKind = tokenKind;
        Token* pToken = m_pParser->EatTokenOverEOLs();

        if (pToken == nullptr)
        {
            return;
        }

        PxAccessKind currAccessKind = m_pContext->m_Scope.m_Access.m_Kind;

        switch (accessTokenKind)
        {
        case TokenKind::KeywordPublic: m_pContext->m_Scope.m_Access.m_Kind = PxAccessKind::Public; break;
        case TokenKind::KeywordPrivate: m_pContext->m_Scope.m_Access.m_Kind = PxAccessKind::Private; break;
        case TokenKind::KeywordProtected: m_pContext->m_Scope.m_Access.m_Kind = PxAccessKind::Protected; break;
        case TokenKind::KeywordPackage: m_pContext->m_Scope.m_Access.m_Kind = PxAccessKind::Package; break;
        case TokenKind::KeywordInternal: m_pContext->m_Scope.m_Access.m_Kind = PxAccessKind::Internal; break;
        default: break;
        }

        BeginSymbol(pSymbolTable, pToken->kind);

        m_pContext->m_Scope.m_Access.m_Kind = currAccessKind;
    }

    void PxSymbolParser::BeginSymbol(PxSymbolTable* pSymbolTable, const TokenKind tokenKind)
    {
        switch (tokenKind)
        {
        case TokenKind::KeywordVar:
        case TokenKind::KeywordVal:
        case TokenKind::KeywordFun:
        case TokenKind::KeywordStruct:
        case TokenKind::KeywordEnum:
        {
            RegisterSymbol(pSymbolTable, tokenKind);
            break;
        }
        case TokenKind::OpenBrace:
        {
            m_pParser->PutBackToken();
            pSymbolTable->Append(ParseScopeMembers());

            break;
        }
        default: break;
        }
    }

    void PxSymbolParser::RegisterSymbol(PxSymbolTable* pSymbolTable, const TokenKind tokenKind)
    {
        struct
        {
            PxUsageKind usageKind = PxUsageKind::Runtime;
            PxDeclKind declKind = PxDeclKind::Invalid;
        } info;

        switch (tokenKind)
        {
        case TokenKind::KeywordVar:
        {
            switch (m_pContext->m_Scope.m_Usage.m_Kind)
            {
            case PxUsageKind::Runtime:
            case PxUsageKind::Comptime:
            case PxUsageKind::Anytime:
            {
                info.usageKind = m_pContext->m_Scope.m_Usage.m_Kind;
                break;
            }
            }

            info.declKind = PxDeclKind::Var;

            break;
        }
        case TokenKind::KeywordVal:
        {
            info.usageKind = m_pContext->m_Scope.m_Usage.m_Kind;
            info.declKind = PxDeclKind::Val;

            break;
        }
        case TokenKind::KeywordFun:
        {
            switch (m_pContext->m_Scope.m_Usage.m_Kind)
            {
            case PxUsageKind::Runtime: return;
            case PxUsageKind::Comptime:
            case PxUsageKind::Anytime:
            {
                info.usageKind = m_pContext->m_Scope.m_Usage.m_Kind;
                break;
            }
            }

            info.declKind = PxDeclKind::Fun;

            break;
        }
        case TokenKind::KeywordStruct:
        {
            switch (m_pContext->m_Scope.m_Usage.m_Kind)
            {
            case PxUsageKind::Runtime:
            {
                info.usageKind = PxUsageKind::Anytime;
                break;
            }
            case PxUsageKind::Comptime:
            case PxUsageKind::Anytime:
            {
                info.usageKind = m_pContext->m_Scope.m_Usage.m_Kind;
                break;
            }
            }

            info.declKind = PxDeclKind::Struct;

            break;
        }
        case TokenKind::KeywordEnum:
        {
            switch (m_pContext->m_Scope.m_Usage.m_Kind)
            {
            case PxUsageKind::Runtime:
            {
                info.usageKind = PxUsageKind::Anytime;
                break;
            }
            case PxUsageKind::Comptime:
            case PxUsageKind::Anytime:
            {
                info.usageKind = m_pContext->m_Scope.m_Usage.m_Kind;
                break;
            }
            }

            info.declKind = PxDeclKind::Enum;

            break;
        }
        default: return;
        }

        if (const auto& pIdentifier = m_pParser->ExpectToken(TokenKind::Identifier); pIdentifier.second)
        {
            PxSymbol symbol
            {
                .m_Name = pIdentifier.first->value,
                .m_Usage = info.usageKind,
                .m_Scope = m_pContext->m_Scope,
                .m_Decl
                {
                    .m_Kind = info.declKind
                },
                .m_Access = m_pContext->m_Scope.m_Access
            };

            switch (tokenKind)
            {
            case TokenKind::KeywordStruct:
            {
                PxScopeKind prevScopeKind = m_pContext->m_Scope.m_Kind;
                m_pContext->m_Scope.m_Kind = PxScopeKind::Struct;

                bool bPrevInsideStruct = m_pContext->m_Scope.m_bInsideStruct;
                m_pContext->m_Scope.m_bInsideStruct = true;

                symbol.m_pSymbolTable = ParseScopeMembers();
                
                m_pContext->m_Scope.m_bInsideStruct = bPrevInsideStruct;
                m_pContext->m_Scope.m_Kind = prevScopeKind;

                break;
            }
            case TokenKind::KeywordEnum:
            {
                // todo. implement
                break;
            }
            default: break;
            }

            pSymbolTable->m_Symbols.push_back(symbol);
        }
    }
}