/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "TokenKind.hpp"

namespace Pollux::Lang
{
	const char* g_pTokenKind_Undefined = "TokenKind::Undefined";
	const char* g_pTokenKind_Eof = "TokenKind::Eof";
	const char* g_pTokenKind_Eol = "TokenKind::Eol";
	const char* g_pTokenKind_Identifier = "TokenKind::Identifier";
	const char* g_pTokenKind_LiteralInteger = "TokenKind::LiteralInteger";
	const char* g_pTokenKind_LiteralDouble = "TokenKind::LiteralDouble";
	const char* g_pTokenKind_LiteralString = "TokenKind::LiteralString";
	const char* g_pTokenKind_OperatorAdd = "TokenKind::OperatorAdd";
	const char* g_pTokenKind_OperatorSub = "TokenKind::OperatorSub";
	const char* g_pTokenKind_OperatorMul = "TokenKind::OperatorMul";
	const char* g_pTokenKind_OperatorDiv = "TokenKind::OperatorDiv";
	const char* g_pTokenKind_OperatorMod = "TokenKind::OperatorMod";
	const char* g_pTokenKind_OperatorPow = "TokenKind::OperatorPow";
	const char* g_pTokenKind_OperatorRoot = "TokenKind::OperatorRoot";
	const char* g_pTokenKind_OperatorAssign = "TokenKind::OperatorAssign";
	const char* g_pTokenKind_OperatorAddAssign = "TokenKind::OperatorAddAssign";
	const char* g_pTokenKind_OperatorSubAssign = "TokenKind::OperatorSubAssign";
	const char* g_pTokenKind_OperatorMulAssign = "TokenKind::OperatorMulAssign";
	const char* g_pTokenKind_OperatorDivAssign = "TokenKind::OperatorDivAssign";
	const char* g_pTokenKind_OperatorModAssign = "TokenKind::OperatorModAssign";
	const char* g_pTokenKind_OperatorPowAssign = "TokenKind::OperatorPowAssign";
	const char* g_pTokenKind_OperatorRootAssign = "TokenKind::OperatorRootAssign";
	const char* g_pTokenKind_OperatorEq = "TokenKind::OperatorEq";
	const char* g_pTokenKind_OperatorNe = "TokenKind::OperatorNe";
	const char* g_pTokenKind_OperatorLe = "TokenKind::OperatorLe";
	const char* g_pTokenKind_OperatorLt = "TokenKind::OperatorLt";
	const char* g_pTokenKind_OperatorGe = "TokenKind::OperatorGe";
	const char* g_pTokenKind_OperatorGt = "TokenKind::OperatorGt";
	const char* g_pTokenKind_OpenParen = "TokenKind::OpenParen";
	const char* g_pTokenKind_CloseParen = "TokenKind::CloseParen";
	const char* g_pTokenKind_OpenBrace = "TokenKind::OpenBrace";
	const char* g_pTokenKind_CloseBrace = "TokenKind::CloseBrace";
	const char* g_pTokenKind_OpenBracket = "TokenKind::OpenBracket";
	const char* g_pTokenKind_CloseBracket = "TokenKind::CloseBracket";
	const char* g_pTokenKind_Colon = "TokenKind::Colon";
	const char* g_pTokenKind_Semicolon = "TokenKind::Semicolon";
	const char* g_pTokenKind_Comma = "TokenKind::Comma";
	const char* g_pTokenKind_Dot = "TokenKind::Dot";
	const char* g_pTokenKind_RangeExclusive = "TokenKind::RangeExclusive";
	const char* g_pTokenKind_RangeInclusive = "TokenKind::RangeInclusive";
	const char* g_pTokenKind_Follow = "TokenKind::Follow";
	const char* g_pTokenKind_Arrow = "TokenKind::Arrow";
	const char* g_pTokenKind_At = "TokenKind::At";
	const char* g_pTokenKind_LogicalNot = "TokenKind::LogicalNot";
	const char* g_pTokenKind_LogicalAnd = "TokenKind::LogicalAnd";
	const char* g_pTokenKind_LogicalOr = "TokenKind::LogicalOr";
	const char* g_pTokenKind_BitNot = "TokenKind::BitNot";
	const char* g_pTokenKind_BitAnd = "TokenKind::BitAnd";
	const char* g_pTokenKind_BitOr = "TokenKind::BitOr";
	const char* g_pTokenKind_BitXor = "TokenKind::BitXor";
	const char* g_pTokenKind_BitLeftShift = "TokenKind::BitLeftShift";
	const char* g_pTokenKind_BitRightShift = "TokenKind::BitRightShift";
	const char* g_pTokenKind_BitUnsignedRightShift = "TokenKind::BitUnsignedRightShift";
	const char* g_pTokenKind_KeywordVar = "TokenKind::KeywordVar";
	const char* g_pTokenKind_KeywordVal = "TokenKind::KeywordVal";
	const char* g_pTokenKind_KeywordTrue = "TokenKind::KeywordTrue";
	const char* g_pTokenKind_KeywordFalse = "TokenKind::KeywordFalse";
	const char* g_pTokenKind_KeywordLog = "TokenKind::KeywordLog";
	const char* g_pTokenKind_KeywordIf = "TokenKind::KeywordIf";
	const char* g_pTokenKind_KeywordElse = "TokenKind::KeywordElse";
	const char* g_pTokenKind_KeywordReturn = "TokenKind::KeywordReturn";
	const char* g_pTokenKind_KeywordFunc = "TokenKind::KeywordFunc";
	const char* g_pTokenKind_KeywordAnnot = "TokenKind::KeywordAnnot";
	const char* g_pTokenKind_KeywordObject = "TokenKind::KeywordObject";
	const char* g_pTokenKind_KeywordClass = "TokenKind::KeywordClass";
	const char* g_pTokenKind_KeywordStruct = "TokenKind::KeywordStruct";
	const char* g_pTokenKind_KeywordEnum = "TokenKind::KeywordEnum";
	const char* g_pTokenKind_KeywordComptime = "TokenKind::KeywordComptime";
	const char* g_pTokenKind_KeywordAlways = "TokenKind::KeywordAlways";
	const char* g_pTokenKind_KeywordPackage = "TokenKind::KeywordPackage";

	const std::map<const char*, TokenKind> g_TokenKindMap
	{
		{ g_pTokenKind_Undefined, TokenKind::Undefined },
		{ g_pTokenKind_Eof, TokenKind::Eof },
		{ g_pTokenKind_Eol, TokenKind::Eol },
		{ g_pTokenKind_Identifier, TokenKind::Identifier },
		{ g_pTokenKind_LiteralInteger, TokenKind::LiteralInteger },
		{ g_pTokenKind_LiteralDouble, TokenKind::LiteralDouble },
		{ g_pTokenKind_LiteralString, TokenKind::LiteralString },
		{ g_pTokenKind_OperatorAdd, TokenKind::OperatorAdd },
		{ g_pTokenKind_OperatorSub, TokenKind::OperatorSub },
		{ g_pTokenKind_OperatorMul, TokenKind::OperatorMul },
		{ g_pTokenKind_OperatorDiv, TokenKind::OperatorDiv },
		{ g_pTokenKind_OperatorMod, TokenKind::OperatorMod },
		{ g_pTokenKind_OperatorPow, TokenKind::OperatorPow },
		{ g_pTokenKind_OperatorRoot, TokenKind::OperatorRoot },
		{ g_pTokenKind_OperatorAssign, TokenKind::OperatorAssign },
		{ g_pTokenKind_OperatorAddAssign, TokenKind::OperatorAddAssign },
		{ g_pTokenKind_OperatorSubAssign, TokenKind::OperatorSubAssign },
		{ g_pTokenKind_OperatorMulAssign, TokenKind::OperatorMulAssign },
		{ g_pTokenKind_OperatorDivAssign, TokenKind::OperatorDivAssign },
		{ g_pTokenKind_OperatorModAssign, TokenKind::OperatorModAssign },
		{ g_pTokenKind_OperatorPowAssign, TokenKind::OperatorPowAssign },
		{ g_pTokenKind_OperatorRootAssign, TokenKind::OperatorRootAssign },
		{ g_pTokenKind_OperatorEq, TokenKind::OperatorEq },
		{ g_pTokenKind_OperatorNe, TokenKind::OperatorNe },
		{ g_pTokenKind_OperatorLe, TokenKind::OperatorLe },
		{ g_pTokenKind_OperatorLt, TokenKind::OperatorLt },
		{ g_pTokenKind_OperatorGe, TokenKind::OperatorGe },
		{ g_pTokenKind_OperatorGt, TokenKind::OperatorGt },
		{ g_pTokenKind_OpenParen, TokenKind::OpenParen },
		{ g_pTokenKind_CloseParen, TokenKind::CloseParen },
		{ g_pTokenKind_OpenBrace, TokenKind::OpenBrace },
		{ g_pTokenKind_CloseBrace, TokenKind::CloseBrace },
		{ g_pTokenKind_OpenBracket, TokenKind::OpenBracket },
		{ g_pTokenKind_CloseBracket, TokenKind::CloseBracket },
		{ g_pTokenKind_Colon, TokenKind::Colon },
		{ g_pTokenKind_Semicolon, TokenKind::Semicolon },
		{ g_pTokenKind_Comma, TokenKind::Comma },
		{ g_pTokenKind_Dot, TokenKind::Dot },
		{ g_pTokenKind_RangeExclusive, TokenKind::RangeExclusive },
		{ g_pTokenKind_RangeInclusive, TokenKind::RangeInclusive },
		{ g_pTokenKind_Follow, TokenKind::Follow },
		{ g_pTokenKind_Arrow, TokenKind::Arrow },
		{ g_pTokenKind_At, TokenKind::At },
		{ g_pTokenKind_LogicalNot, TokenKind::LogicalNot },
		{ g_pTokenKind_LogicalAnd, TokenKind::LogicalAnd },
		{ g_pTokenKind_LogicalOr, TokenKind::LogicalOr },
		{ g_pTokenKind_BitNot, TokenKind::BitNot },
		{ g_pTokenKind_BitAnd, TokenKind::BitAnd },
		{ g_pTokenKind_BitOr, TokenKind::BitOr },
		{ g_pTokenKind_BitXor, TokenKind::BitXor },
		{ g_pTokenKind_BitLeftShift, TokenKind::BitLeftShift },
		{ g_pTokenKind_BitRightShift, TokenKind::BitRightShift },
		{ g_pTokenKind_BitUnsignedRightShift, TokenKind::BitUnsignedRightShift },
		{ g_pTokenKind_KeywordVar, TokenKind::KeywordVar },
		{ g_pTokenKind_KeywordVal, TokenKind::KeywordVal },
		{ g_pTokenKind_KeywordTrue, TokenKind::KeywordTrue },
		{ g_pTokenKind_KeywordFalse, TokenKind::KeywordFalse },
		{ g_pTokenKind_KeywordLog, TokenKind::KeywordLog },
		{ g_pTokenKind_KeywordIf, TokenKind::KeywordIf },
		{ g_pTokenKind_KeywordElse, TokenKind::KeywordElse },
		{ g_pTokenKind_KeywordReturn, TokenKind::KeywordReturn },
		{ g_pTokenKind_KeywordFunc, TokenKind::KeywordFunc },
		{ g_pTokenKind_KeywordAnnot, TokenKind::KeywordAnnot },
		{ g_pTokenKind_KeywordObject, TokenKind::KeywordObject },
		{ g_pTokenKind_KeywordClass, TokenKind::KeywordClass },
		{ g_pTokenKind_KeywordStruct, TokenKind::KeywordStruct },
		{ g_pTokenKind_KeywordEnum, TokenKind::KeywordEnum },
		{ g_pTokenKind_KeywordComptime, TokenKind::KeywordComptime },
		{ g_pTokenKind_KeywordAlways, TokenKind::KeywordAlways },
		{ g_pTokenKind_KeywordPackage, TokenKind::KeywordPackage }
	};

	TokenKind TokenKindToEnum(const char* tokenKind)
	{
		if (g_TokenKindMap.contains(tokenKind))
		{
			return g_TokenKindMap.at(tokenKind);
		}

		throw std::runtime_error("Error (Lang.Tokenizer): Token Kind string is not valid.");
	}

	std::string ToString(const TokenKind tokenKind)
	{
		switch (tokenKind)
		{
		case TokenKind::Undefined: return g_pTokenKind_Undefined;
		case TokenKind::Eof: return g_pTokenKind_Eof;
		case TokenKind::Eol: return g_pTokenKind_Eol;
		case TokenKind::Identifier: return g_pTokenKind_Identifier;
		case TokenKind::LiteralInteger: return g_pTokenKind_LiteralInteger;
		case TokenKind::LiteralDouble: return g_pTokenKind_LiteralDouble;
		case TokenKind::LiteralString: return g_pTokenKind_LiteralString;
		case TokenKind::OperatorAdd: return g_pTokenKind_OperatorAdd;
		case TokenKind::OperatorSub: return g_pTokenKind_OperatorSub;
		case TokenKind::OperatorMul: return g_pTokenKind_OperatorMul;
		case TokenKind::OperatorDiv: return g_pTokenKind_OperatorDiv;
		case TokenKind::OperatorMod: return g_pTokenKind_OperatorMod;
		case TokenKind::OperatorPow: return g_pTokenKind_OperatorPow;
		case TokenKind::OperatorRoot: return g_pTokenKind_OperatorRoot;
		case TokenKind::OperatorAssign: return g_pTokenKind_OperatorAssign;
		case TokenKind::OperatorAddAssign: return g_pTokenKind_OperatorAddAssign;
		case TokenKind::OperatorSubAssign: return g_pTokenKind_OperatorSubAssign;
		case TokenKind::OperatorMulAssign: return g_pTokenKind_OperatorMulAssign;
		case TokenKind::OperatorDivAssign: return g_pTokenKind_OperatorDivAssign;
		case TokenKind::OperatorModAssign: return g_pTokenKind_OperatorModAssign;
		case TokenKind::OperatorPowAssign: return g_pTokenKind_OperatorPowAssign;
		case TokenKind::OperatorRootAssign: return g_pTokenKind_OperatorRootAssign;
		case TokenKind::OperatorEq: return g_pTokenKind_OperatorEq;
		case TokenKind::OperatorNe: return g_pTokenKind_OperatorNe;
		case TokenKind::OperatorLe: return g_pTokenKind_OperatorLe;
		case TokenKind::OperatorLt: return g_pTokenKind_OperatorLt;
		case TokenKind::OperatorGe: return g_pTokenKind_OperatorGe;
		case TokenKind::OperatorGt: return g_pTokenKind_OperatorGt;
		case TokenKind::OpenParen: return g_pTokenKind_OpenParen;
		case TokenKind::CloseParen: return g_pTokenKind_CloseParen;
		case TokenKind::OpenBrace: return g_pTokenKind_OpenBrace;
		case TokenKind::CloseBrace: return g_pTokenKind_CloseBrace;
		case TokenKind::OpenBracket: return g_pTokenKind_OpenBracket;
		case TokenKind::CloseBracket: return g_pTokenKind_CloseBracket;
		case TokenKind::Colon: return g_pTokenKind_Colon;
		case TokenKind::Semicolon: return g_pTokenKind_Semicolon;
		case TokenKind::Comma: return g_pTokenKind_Comma;
		case TokenKind::Dot: return g_pTokenKind_Dot;
		case TokenKind::RangeExclusive: return g_pTokenKind_RangeExclusive;
		case TokenKind::RangeInclusive: return g_pTokenKind_RangeInclusive;
		case TokenKind::Follow: return g_pTokenKind_Follow;
		case TokenKind::Arrow: return g_pTokenKind_Arrow;
		case TokenKind::At: return g_pTokenKind_At;
		case TokenKind::LogicalNot: return g_pTokenKind_LogicalNot;
		case TokenKind::LogicalAnd: return g_pTokenKind_LogicalAnd;
		case TokenKind::LogicalOr: return g_pTokenKind_LogicalOr;
		case TokenKind::BitNot: return g_pTokenKind_BitNot;
		case TokenKind::BitAnd: return g_pTokenKind_BitAnd;
		case TokenKind::BitOr: return g_pTokenKind_BitOr;
		case TokenKind::BitXor: return g_pTokenKind_BitXor;
		case TokenKind::BitLeftShift: return g_pTokenKind_BitLeftShift;
		case TokenKind::BitRightShift: return g_pTokenKind_BitRightShift;
		case TokenKind::BitUnsignedRightShift: return g_pTokenKind_BitUnsignedRightShift;
		case TokenKind::KeywordVar: return g_pTokenKind_KeywordVar;
		case TokenKind::KeywordVal: return g_pTokenKind_KeywordVal;
		case TokenKind::KeywordTrue: return g_pTokenKind_KeywordTrue;
		case TokenKind::KeywordFalse: return g_pTokenKind_KeywordFalse;
		case TokenKind::KeywordLog: return g_pTokenKind_KeywordLog;
		case TokenKind::KeywordIf: return g_pTokenKind_KeywordIf;
		case TokenKind::KeywordElse: return g_pTokenKind_KeywordElse;
		case TokenKind::KeywordReturn: return g_pTokenKind_KeywordReturn;
		case TokenKind::KeywordFunc: return g_pTokenKind_KeywordFunc;
		case TokenKind::KeywordAnnot: return g_pTokenKind_KeywordAnnot;
		case TokenKind::KeywordObject: return g_pTokenKind_KeywordObject;
		case TokenKind::KeywordClass: return g_pTokenKind_KeywordClass;
		case TokenKind::KeywordStruct: return g_pTokenKind_KeywordStruct;
		case TokenKind::KeywordEnum: return g_pTokenKind_KeywordEnum;
		case TokenKind::KeywordComptime: return g_pTokenKind_KeywordComptime;
		case TokenKind::KeywordAlways: return g_pTokenKind_KeywordAlways;
		case TokenKind::KeywordPackage: return g_pTokenKind_KeywordPackage;
		default: ; // todo. Log a warning message
		}

		return g_pEmptyString;
	}
}