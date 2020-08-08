/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	/*************************************************************************************************************************
	 * \enum Token Kind
	 *************************************************************************************************************************/
	enum class TokenKind
	{
		Undefined,				///	null
		Eof,					///	-1
		Eol,					///	\n
		Identifier,				///	name
		LiteralBinary,			/// e.g. 0b0101
		LiteralOctal,			/// e.g. 0o5702
		LiteralHexa,			/// e.g. 0xAF62
		LiteralInteger,			///	e.g. 58
		LiteralFloat,			/// e.g. 58f, 58.f, 58.0f
		LiteralDouble,			///	e.g. 58.0
		LiteralString,			///	e.g. "hello world"
		OperatorAdd,			///	+
		OperatorSub,			///	-
		OperatorMul,			///	*
		OperatorDiv,			///	/
		OperatorMod,			///	%
		OperatorPow,			///	**
		OperatorRoot,			///	//
		OperatorAssign,			///	=
		OperatorAddAssign,		///	+=
		OperatorSubAssign,		///	-=
		OperatorMulAssign,		///	*=
		OperatorDivAssign,		///	/=
		OperatorModAssign,		///	%=
		OperatorPowAssign,		///	**=
		OperatorRootAssign,		///	//=
		OperatorEq,				///	==
		OperatorNe,				///	!=
		OperatorLe,				///	<=
		OperatorLt,				///	<
		OperatorGe,				///	>=
		OperatorGt,				///	>
		OpenParen,				///	(
		CloseParen,				///	)
		OpenBrace,				///	{
		CloseBrace,				///	}
		OpenBracket,			///	[
		CloseBracket,			///	]
		Colon,					///	:
		Semicolon,				///	;
		Comma,					///	,
		Dot,					///	.
		RangeExclusive,			///	..
		RangeInclusive,			///	..=
		Follow,					///	=>
		Arrow,					///	->
		At,						/// @
		LogicalNot,				///	!
		LogicalAnd,				///	&&
		LogicalOr,				///	||
		BitNot,					///	~
		BitAnd,					///	&
		BitOr,					///	|
		BitXor,					///	^
		BitLeftShift,			/// <<
		BitRightShift,			/// >>
		BitUnsignedRightShift,	/// >>>
		KeywordVar,				///	var
		KeywordVal,				///	val
		KeywordTrue,			///	true
		KeywordFalse,			///	false
		KeywordLog,				///	log
		KeywordIf,				///	if
		KeywordElse,			///	else
		KeywordReturn,			///	return
		KeywordFun,				///	fun
		KeywordAnnot,			///	annot
		KeywordObject,			/// object
		KeywordClass,			/// class
		KeywordStruct,			/// struct
		KeywordEnum,			/// enum
		KeywordComptime,		///	comptime
		KeywordAlways,			///	always
		KeywordUnit,			///	unit
		KeywordUse,				/// use
	};

	extern const std::string g_pTokenKind_Undefined;
	
	extern const std::string g_pTokenKind_Eof;
	
	extern const std::string g_pTokenKind_Eol;
	
	extern const std::string g_pTokenKind_Identifier;
	
	extern const std::string g_pTokenKind_LiteralBinary;
	
	extern const std::string g_pTokenKind_LiteralOctal;
	
	extern const std::string g_pTokenKind_LiteralHexa;
	
	extern const std::string g_pTokenKind_LiteralInteger;
	
	extern const std::string g_pTokenKind_LiteralFloat;
	
	extern const std::string g_pTokenKind_LiteralDouble;
	
	extern const std::string g_pTokenKind_LiteralString;
	
	extern const std::string g_pTokenKind_OperatorAdd;
	
	extern const std::string g_pTokenKind_OperatorSub;
	
	extern const std::string g_pTokenKind_OperatorMul;
	
	extern const std::string g_pTokenKind_OperatorDiv;
	
	extern const std::string g_pTokenKind_OperatorMod;
	
	extern const std::string g_pTokenKind_OperatorPow;
	
	extern const std::string g_pTokenKind_OperatorRoot;
	
	extern const std::string g_pTokenKind_OperatorAssign;
	
	extern const std::string g_pTokenKind_OperatorAddAssign;
	
	extern const std::string g_pTokenKind_OperatorSubAssign;
	
	extern const std::string g_pTokenKind_OperatorMulAssign;
	
	extern const std::string g_pTokenKind_OperatorDivAssign;
	
	extern const std::string g_pTokenKind_OperatorModAssign;
	
	extern const std::string g_pTokenKind_OperatorPowAssign;
	
	extern const std::string g_pTokenKind_OperatorRootAssign;
	
	extern const std::string g_pTokenKind_OperatorEq;
	
	extern const std::string g_pTokenKind_OperatorNe;
	
	extern const std::string g_pTokenKind_OperatorLe;
	
	extern const std::string g_pTokenKind_OperatorLt;
	
	extern const std::string g_pTokenKind_OperatorGe;
	
	extern const std::string g_pTokenKind_OperatorGt;
	
	extern const std::string g_pTokenKind_OpenParen;
	
	extern const std::string g_pTokenKind_CloseParen;
	
	extern const std::string g_pTokenKind_OpenBrace;
	
	extern const std::string g_pTokenKind_CloseBrace;
	
	extern const std::string g_pTokenKind_OpenBracket;
	
	extern const std::string g_pTokenKind_CloseBracket;
	
	extern const std::string g_pTokenKind_Colon;
	
	extern const std::string g_pTokenKind_Semicolon;
	
	extern const std::string g_pTokenKind_Comma;
	
	extern const std::string g_pTokenKind_Dot;
	
	extern const std::string g_pTokenKind_RangeExclusive;
	
	extern const std::string g_pTokenKind_RangeInclusive;
	
	extern const std::string g_pTokenKind_Follow;
	
	extern const std::string g_pTokenKind_Arrow;
	
	extern const std::string g_pTokenKind_At;
	
	extern const std::string g_pTokenKind_LogicalNot;
	
	extern const std::string g_pTokenKind_LogicalAnd;
	
	extern const std::string g_pTokenKind_LogicalOr;
	
	extern const std::string g_pTokenKind_BitNot;
	
	extern const std::string g_pTokenKind_BitAnd;
	
	extern const std::string g_pTokenKind_BitOr;
	
	extern const std::string g_pTokenKind_BitXor;
	
	extern const std::string g_pTokenKind_BitLeftShift;
	
	extern const std::string g_pTokenKind_BitRightShift;
	
	extern const std::string g_pTokenKind_BitUnsignedRightShift;
	
	extern const std::string g_pTokenKind_KeywordVar;
	
	extern const std::string g_pTokenKind_KeywordVal;
	
	extern const std::string g_pTokenKind_KeywordTrue;
	
	extern const std::string g_pTokenKind_KeywordFalse;
	
	extern const std::string g_pTokenKind_KeywordLog;
	
	extern const std::string g_pTokenKind_KeywordIf;
	
	extern const std::string g_pTokenKind_KeywordElse;
	
	extern const std::string g_pTokenKind_KeywordReturn;
	
	extern const std::string g_pTokenKind_KeywordFun;
	
	extern const std::string g_pTokenKind_KeywordAnnot;
	
	extern const std::string g_pTokenKind_KeywordObject;
	
	extern const std::string g_pTokenKind_KeywordClass;
	
	extern const std::string g_pTokenKind_KeywordStruct;
	
	extern const std::string g_pTokenKind_KeywordEnum;
	
	extern const std::string g_pTokenKind_KeywordComptime;
	
	extern const std::string g_pTokenKind_KeywordAlways;
	
	extern const std::string g_pTokenKind_KeywordUnit;

	extern const std::string g_pTokenKind_KeywordUse;

	extern const std::map<std::string, TokenKind> g_TokenKindMap;

	extern const std::map<std::string, TokenKind> g_TokenKindKeywordMap;

	TokenKind TokenKindToEnum(const std::string& tokenKind);

	std::string ToString(const TokenKind tokenKind);
}