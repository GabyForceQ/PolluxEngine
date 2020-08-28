/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "TokenKind.hpp"

namespace Pollux::Lang
{
	const std::string g_pTokenKind_Undefined = "TokenKind::Undefined";
	const std::string g_pTokenKind_Eof = "TokenKind::Eof";
	const std::string g_pTokenKind_Eol = "TokenKind::Eol";
	const std::string g_pTokenKind_Identifier = "TokenKind::Identifier";
	const std::string g_pTokenKind_LiteralBinary = "TokenKind::LiteralBinary";
	const std::string g_pTokenKind_LiteralOctal = "TokenKind::LiteralOctal";
	const std::string g_pTokenKind_LiteralHexa = "TokenKind::LiteralHexa";
	const std::string g_pTokenKind_LiteralInteger = "TokenKind::LiteralInteger";
	const std::string g_pTokenKind_LiteralFloat = "TokenKind::LiteralFloat";
	const std::string g_pTokenKind_LiteralDouble = "TokenKind::LiteralDouble";
	const std::string g_pTokenKind_LiteralString = "TokenKind::LiteralString";
	const std::string g_pTokenKind_OperatorAdd = "TokenKind::OperatorAdd";
	const std::string g_pTokenKind_OperatorSub = "TokenKind::OperatorSub";
	const std::string g_pTokenKind_OperatorMul = "TokenKind::OperatorMul";
	const std::string g_pTokenKind_OperatorDiv = "TokenKind::OperatorDiv";
	const std::string g_pTokenKind_OperatorMod = "TokenKind::OperatorMod";
	const std::string g_pTokenKind_OperatorPow = "TokenKind::OperatorPow";
	const std::string g_pTokenKind_OperatorRoot = "TokenKind::OperatorRoot";
	const std::string g_pTokenKind_OperatorAssign = "TokenKind::OperatorAssign";
	const std::string g_pTokenKind_OperatorAddAssign = "TokenKind::OperatorAddAssign";
	const std::string g_pTokenKind_OperatorSubAssign = "TokenKind::OperatorSubAssign";
	const std::string g_pTokenKind_OperatorMulAssign = "TokenKind::OperatorMulAssign";
	const std::string g_pTokenKind_OperatorDivAssign = "TokenKind::OperatorDivAssign";
	const std::string g_pTokenKind_OperatorModAssign = "TokenKind::OperatorModAssign";
	const std::string g_pTokenKind_OperatorPowAssign = "TokenKind::OperatorPowAssign";
	const std::string g_pTokenKind_OperatorRootAssign = "TokenKind::OperatorRootAssign";
	const std::string g_pTokenKind_OperatorEq = "TokenKind::OperatorEq";
	const std::string g_pTokenKind_OperatorNe = "TokenKind::OperatorNe";
	const std::string g_pTokenKind_OperatorLe = "TokenKind::OperatorLe";
	const std::string g_pTokenKind_OperatorLt = "TokenKind::OperatorLt";
	const std::string g_pTokenKind_OperatorGe = "TokenKind::OperatorGe";
	const std::string g_pTokenKind_OperatorGt = "TokenKind::OperatorGt";
	const std::string g_pTokenKind_OpenParen = "TokenKind::OpenParen";
	const std::string g_pTokenKind_CloseParen = "TokenKind::CloseParen";
	const std::string g_pTokenKind_OpenBrace = "TokenKind::OpenBrace";
	const std::string g_pTokenKind_CloseBrace = "TokenKind::CloseBrace";
	const std::string g_pTokenKind_OpenBracket = "TokenKind::OpenBracket";
	const std::string g_pTokenKind_CloseBracket = "TokenKind::CloseBracket";
	const std::string g_pTokenKind_Colon = "TokenKind::Colon";
	const std::string g_pTokenKind_Semicolon = "TokenKind::Semicolon";
	const std::string g_pTokenKind_Comma = "TokenKind::Comma";
	const std::string g_pTokenKind_Dot = "TokenKind::Dot";
	const std::string g_pTokenKind_RangeExclusive = "TokenKind::RangeExclusive";
	const std::string g_pTokenKind_RangeInclusive = "TokenKind::RangeInclusive";
	const std::string g_pTokenKind_Follow = "TokenKind::Follow";
	const std::string g_pTokenKind_Arrow = "TokenKind::Arrow";
	const std::string g_pTokenKind_At = "TokenKind::At";
	const std::string g_pTokenKind_LogicalNot = "TokenKind::LogicalNot";
	const std::string g_pTokenKind_LogicalAnd = "TokenKind::LogicalAnd";
	const std::string g_pTokenKind_LogicalOr = "TokenKind::LogicalOr";
	const std::string g_pTokenKind_BitNot = "TokenKind::BitNot";
	const std::string g_pTokenKind_BitAnd = "TokenKind::BitAnd";
	const std::string g_pTokenKind_BitOr = "TokenKind::BitOr";
	const std::string g_pTokenKind_BitXor = "TokenKind::BitXor";
	const std::string g_pTokenKind_BitLeftShift = "TokenKind::BitLeftShift";
	const std::string g_pTokenKind_BitRightShift = "TokenKind::BitRightShift";
	const std::string g_pTokenKind_BitUnsignedRightShift = "TokenKind::BitUnsignedRightShift";
	const std::string g_pTokenKind_KeywordVar = "TokenKind::KeywordVar";
	const std::string g_pTokenKind_KeywordVal = "TokenKind::KeywordVal";
	const std::string g_pTokenKind_KeywordTrue = "TokenKind::KeywordTrue";
	const std::string g_pTokenKind_KeywordFalse = "TokenKind::KeywordFalse";
	const std::string g_pTokenKind_KeywordLog = "TokenKind::KeywordLog";
	const std::string g_pTokenKind_KeywordIf = "TokenKind::KeywordIf";
	const std::string g_pTokenKind_KeywordElse = "TokenKind::KeywordElse";
	const std::string g_pTokenKind_KeywordReturn = "TokenKind::KeywordReturn";
	const std::string g_pTokenKind_KeywordFun = "TokenKind::KeywordFun";
	const std::string g_pTokenKind_KeywordAnnot = "TokenKind::KeywordAnnot";
	const std::string g_pTokenKind_KeywordObject = "TokenKind::KeywordObject";
	const std::string g_pTokenKind_KeywordClass = "TokenKind::KeywordClass";
	const std::string g_pTokenKind_KeywordStruct = "TokenKind::KeywordStruct";
	const std::string g_pTokenKind_KeywordEnum = "TokenKind::KeywordEnum";
	const std::string g_pTokenKind_KeywordRuntime = "TokenKind::KeywordRuntime";
	const std::string g_pTokenKind_KeywordComptime = "TokenKind::KeywordComptime";
	const std::string g_pTokenKind_KeywordAnytime = "TokenKind::KeywordAnytime";
	const std::string g_pTokenKind_KeywordUnit = "TokenKind::KeywordUnit";
	const std::string g_pTokenKind_KeywordUse = "TokenKind::KeywordUse";
	const std::string g_pTokenKind_KeywordPublic = "TokenKind::KeywordPublic";
	const std::string g_pTokenKind_KeywordPrivate = "TokenKind::KeywordPrivate";
	const std::string g_pTokenKind_KeywordProtected = "TokenKind::KeywordProtected";
	const std::string g_pTokenKind_KeywordPackage = "TokenKind::KeywordPackage";
	const std::string g_pTokenKind_KeywordInternal = "TokenKind::KeywordInternal";
	const std::string g_pTokenKind_KeywordOpen = "TokenKind::KeywordOpen";
	const std::string g_pTokenKind_KeywordGet = "TokenKind::KeywordGet";
	const std::string g_pTokenKind_KeywordSet = "TokenKind::KeywordSet";
	const std::string g_pTokenKind_KeywordField = "TokenKind::KeywordField";

	const std::map<std::string, TokenKind> g_TokenKindMap
	{
		{ g_pTokenKind_Undefined, TokenKind::Undefined },
		{ g_pTokenKind_Eof, TokenKind::Eof },
		{ g_pTokenKind_Eol, TokenKind::Eol },
		{ g_pTokenKind_Identifier, TokenKind::Identifier },
		{ g_pTokenKind_LiteralBinary, TokenKind::LiteralBinary },
		{ g_pTokenKind_LiteralOctal, TokenKind::LiteralOctal },
		{ g_pTokenKind_LiteralHexa, TokenKind::LiteralHexa },
		{ g_pTokenKind_LiteralInteger, TokenKind::LiteralInteger },
		{ g_pTokenKind_LiteralFloat, TokenKind::LiteralFloat },
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
		{ g_pTokenKind_KeywordFun, TokenKind::KeywordFun },
		{ g_pTokenKind_KeywordAnnot, TokenKind::KeywordAnnot },
		{ g_pTokenKind_KeywordObject, TokenKind::KeywordObject },
		{ g_pTokenKind_KeywordClass, TokenKind::KeywordClass },
		{ g_pTokenKind_KeywordStruct, TokenKind::KeywordStruct },
		{ g_pTokenKind_KeywordEnum, TokenKind::KeywordEnum },
		{ g_pTokenKind_KeywordRuntime, TokenKind::KeywordRuntime },
		{ g_pTokenKind_KeywordComptime, TokenKind::KeywordComptime },
		{ g_pTokenKind_KeywordAnytime, TokenKind::KeywordAnytime },
		{ g_pTokenKind_KeywordUse, TokenKind::KeywordUse },
		{ g_pTokenKind_KeywordPublic, TokenKind::KeywordPublic },
		{ g_pTokenKind_KeywordPrivate, TokenKind::KeywordPrivate },
		{ g_pTokenKind_KeywordProtected, TokenKind::KeywordProtected },
		{ g_pTokenKind_KeywordPackage, TokenKind::KeywordPackage },
		{ g_pTokenKind_KeywordInternal, TokenKind::KeywordInternal },
		{ g_pTokenKind_KeywordOpen, TokenKind::KeywordOpen },
		{ g_pTokenKind_KeywordGet, TokenKind::KeywordGet },
		{ g_pTokenKind_KeywordSet, TokenKind::KeywordSet },
		{ g_pTokenKind_KeywordField, TokenKind::KeywordField }
	};

	const std::map<std::string, TokenKind> g_TokenKindKeywordMap
	{
		{ "var", TokenKind::KeywordVar },
		{ "val", TokenKind::KeywordVal },
		{ "true", TokenKind::KeywordTrue },
		{ "false", TokenKind::KeywordFalse },
		{ "log", TokenKind::KeywordLog },
		{ "if", TokenKind::KeywordIf },
		{ "else", TokenKind::KeywordElse },
		{ "return", TokenKind::KeywordReturn },
		{ "fun", TokenKind::KeywordFun },
		{ "annot", TokenKind::KeywordAnnot },
		{ "object", TokenKind::KeywordObject },
		{ "class", TokenKind::KeywordClass },
		{ "struct", TokenKind::KeywordStruct },
		{ "enum", TokenKind::KeywordEnum },
		{ "runtime", TokenKind::KeywordRuntime },
		{ "comptime", TokenKind::KeywordComptime },
		{ "anytime", TokenKind::KeywordAnytime },
		{ "use", TokenKind::KeywordUse },
		{ "public", TokenKind::KeywordPublic },
		{ "private", TokenKind::KeywordPrivate },
		{ "protected", TokenKind::KeywordProtected },
		{ "package", TokenKind::KeywordPackage },
		{ "internal", TokenKind::KeywordInternal },
		{ "open", TokenKind::KeywordOpen },
		{ "get", TokenKind::KeywordGet },
		{ "set", TokenKind::KeywordSet },
		{ "field", TokenKind::KeywordField }
	};

	TokenKind TokenKindToEnum(const std::string& tokenKind)
	{
		if (g_TokenKindMap.contains(tokenKind))
		{
			return g_TokenKindMap.at(tokenKind);
		}

		throw std::runtime_error("Error (Lang.Tokenizer): TokenKind string is not valid.");
	}

	std::string ToString(const TokenKind tokenKind)
	{
		switch (tokenKind)
		{
		case TokenKind::Undefined: return g_pTokenKind_Undefined;
		case TokenKind::Eof: return g_pTokenKind_Eof;
		case TokenKind::Eol: return g_pTokenKind_Eol;
		case TokenKind::Identifier: return g_pTokenKind_Identifier;
		case TokenKind::LiteralBinary: return g_pTokenKind_LiteralBinary;
		case TokenKind::LiteralOctal: return g_pTokenKind_LiteralOctal;
		case TokenKind::LiteralHexa: return g_pTokenKind_LiteralHexa;
		case TokenKind::LiteralInteger: return g_pTokenKind_LiteralInteger;
		case TokenKind::LiteralFloat: return g_pTokenKind_LiteralFloat;
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
		case TokenKind::KeywordFun: return g_pTokenKind_KeywordFun;
		case TokenKind::KeywordAnnot: return g_pTokenKind_KeywordAnnot;
		case TokenKind::KeywordObject: return g_pTokenKind_KeywordObject;
		case TokenKind::KeywordClass: return g_pTokenKind_KeywordClass;
		case TokenKind::KeywordStruct: return g_pTokenKind_KeywordStruct;
		case TokenKind::KeywordEnum: return g_pTokenKind_KeywordEnum;
		case TokenKind::KeywordRuntime: return g_pTokenKind_KeywordRuntime;
		case TokenKind::KeywordComptime: return g_pTokenKind_KeywordComptime;
		case TokenKind::KeywordAnytime: return g_pTokenKind_KeywordAnytime;
		case TokenKind::KeywordUse: return g_pTokenKind_KeywordUse;
		case TokenKind::KeywordPublic: return g_pTokenKind_KeywordPublic;
		case TokenKind::KeywordPrivate: return g_pTokenKind_KeywordPrivate;
		case TokenKind::KeywordProtected: return g_pTokenKind_KeywordProtected;
		case TokenKind::KeywordPackage: return g_pTokenKind_KeywordPackage;
		case TokenKind::KeywordInternal: return g_pTokenKind_KeywordInternal;
		case TokenKind::KeywordOpen: return g_pTokenKind_KeywordOpen;
		case TokenKind::KeywordGet: return g_pTokenKind_KeywordGet;
		case TokenKind::KeywordSet: return g_pTokenKind_KeywordSet;
		case TokenKind::KeywordField: return g_pTokenKind_KeywordField;
		}

		return g_pEmptyString;
	}
}