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
		LiteralInteger,			///	e.g. 58
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
		KeywordFunc,			///	func
		KeywordAnnot,			///	annot
		KeywordObject,			/// object
		KeywordClass,			/// class
		KeywordStruct,			/// struct
		KeywordEnum,			/// enum
		KeywordComptime,		///	comptime
		KeywordAlways,			///	always
		KeywordPackage			///	package
	};

	extern const char* g_pTokenKind_Undefined;
	extern const char* g_pTokenKind_Eof;
	extern const char* g_pTokenKind_Eol;
	extern const char* g_pTokenKind_Identifier;
	extern const char* g_pTokenKind_LiteralInteger;
	extern const char* g_pTokenKind_LiteralDouble;
	extern const char* g_pTokenKind_LiteralString;
	extern const char* g_pTokenKind_OperatorAdd;
	extern const char* g_pTokenKind_OperatorSub;
	extern const char* g_pTokenKind_OperatorMul;
	extern const char* g_pTokenKind_OperatorDiv;
	extern const char* g_pTokenKind_OperatorMod;
	extern const char* g_pTokenKind_OperatorPow;
	extern const char* g_pTokenKind_OperatorRoot;
	extern const char* g_pTokenKind_OperatorAssign;
	extern const char* g_pTokenKind_OperatorAddAssign;
	extern const char* g_pTokenKind_OperatorSubAssign;
	extern const char* g_pTokenKind_OperatorMulAssign;
	extern const char* g_pTokenKind_OperatorDivAssign;
	extern const char* g_pTokenKind_OperatorModAssign;
	extern const char* g_pTokenKind_OperatorPowAssign;
	extern const char* g_pTokenKind_OperatorRootAssign;
	extern const char* g_pTokenKind_OperatorEq;
	extern const char* g_pTokenKind_OperatorNe;
	extern const char* g_pTokenKind_OperatorLe;
	extern const char* g_pTokenKind_OperatorLt;
	extern const char* g_pTokenKind_OperatorGe;
	extern const char* g_pTokenKind_OperatorGt;
	extern const char* g_pTokenKind_OpenParen;
	extern const char* g_pTokenKind_CloseParen;
	extern const char* g_pTokenKind_OpenBrace;
	extern const char* g_pTokenKind_CloseBrace;
	extern const char* g_pTokenKind_OpenBracket;
	extern const char* g_pTokenKind_CloseBracket;
	extern const char* g_pTokenKind_Colon;
	extern const char* g_pTokenKind_Semicolon;
	extern const char* g_pTokenKind_Comma;
	extern const char* g_pTokenKind_Dot;
	extern const char* g_pTokenKind_RangeExclusive;
	extern const char* g_pTokenKind_RangeInclusive;
	extern const char* g_pTokenKind_Follow;
	extern const char* g_pTokenKind_Arrow;
	extern const char* g_pTokenKind_At;
	extern const char* g_pTokenKind_LogicalNot;
	extern const char* g_pTokenKind_LogicalAnd;
	extern const char* g_pTokenKind_LogicalOr;
	extern const char* g_pTokenKind_BitNot;
	extern const char* g_pTokenKind_BitAnd;
	extern const char* g_pTokenKind_BitOr;
	extern const char* g_pTokenKind_BitXor;
	extern const char* g_pTokenKind_BitLeftShift;
	extern const char* g_pTokenKind_BitRightShift;
	extern const char* g_pTokenKind_BitUnsignedRightShift;
	extern const char* g_pTokenKind_KeywordVar;
	extern const char* g_pTokenKind_KeywordVal;
	extern const char* g_pTokenKind_KeywordTrue;
	extern const char* g_pTokenKind_KeywordFalse;
	extern const char* g_pTokenKind_KeywordLog;
	extern const char* g_pTokenKind_KeywordIf;
	extern const char* g_pTokenKind_KeywordElse;
	extern const char* g_pTokenKind_KeywordReturn;
	extern const char* g_pTokenKind_KeywordFunc;
	extern const char* g_pTokenKind_KeywordAnnot;
	extern const char* g_pTokenKind_KeywordObject;
	extern const char* g_pTokenKind_KeywordClass;
	extern const char* g_pTokenKind_KeywordStruct;
	extern const char* g_pTokenKind_KeywordEnum;
	extern const char* g_pTokenKind_KeywordComptime;
	extern const char* g_pTokenKind_KeywordAlways;
	extern const char* g_pTokenKind_KeywordPackage;

	extern const std::map<const char*, TokenKind> g_TokenKindMap;

	TokenKind TokenKindToEnum(const char* tokenKind);
	std::string ToString(const TokenKind tokenKind);
}