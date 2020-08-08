/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Lexer.hpp"

#define DIGIT_NON_ZERO \
         '1': \
    case '2': \
    case '3': \
    case '4': \
    case '5': \
    case '6': \
    case '7': \
    case '8': \
    case '9'

#define DIGIT \
         '0': \
    case DIGIT_NON_ZERO

#define ALPHA \
         'a': \
    case 'b': \
    case 'c': \
    case 'd': \
    case 'e': \
    case 'f': \
    case 'g': \
    case 'h': \
    case 'i': \
    case 'j': \
    case 'k': \
    case 'l': \
    case 'm': \
    case 'n': \
    case 'o': \
    case 'p': \
    case 'q': \
    case 'r': \
    case 's': \
    case 't': \
    case 'u': \
    case 'v': \
    case 'w': \
    case 'x': \
    case 'y': \
    case 'z': \
    case 'A': \
    case 'B': \
    case 'C': \
    case 'D': \
    case 'E': \
    case 'F': \
    case 'G': \
    case 'H': \
    case 'I': \
    case 'J': \
    case 'K': \
    case 'L': \
    case 'M': \
    case 'N': \
    case 'O': \
    case 'P': \
    case 'Q': \
    case 'R': \
    case 'S': \
    case 'T': \
    case 'U': \
    case 'V': \
    case 'W': \
    case 'X': \
    case 'Y': \
    case 'Z'

#define SYMBOL_CHAR \
    ALPHA: \
    case DIGIT: \
    case '_'

#define SYMBOL_START \
    ALPHA: \
    case '_'

inline bool IsDigitNonZero(char c)
{
	switch (c)
	{
	case DIGIT_NON_ZERO: return true;
	default: return false;
	}
}

inline bool IsDigit(char c)
{
	switch (c)
	{
	case DIGIT: return true;
	default: return false;
	}
}

inline bool IsAlpha(char c)
{
	switch (c)
	{
	case ALPHA: return true;
	default: return false;
	}
}

inline bool IsSymbolChar(char c)
{
	switch (c)
	{
	case SYMBOL_CHAR: return true;
	default: return false;
	}
}

inline bool IsSymbolStart(char c)
{
	switch (c)
	{
	case SYMBOL_START: return true;
	default: return false;
	}
}

namespace Pollux::Lang
{
	Lexer::Lexer(std::string text) noexcept
		:
		text{ std::move(text) },
		currentChar{ this->text[position] }
	{
	}

	void Lexer::Advance()
	{
		position += 1;

		if (position > text.length() - 1)
		{
			currentChar = EOF;
		}
		else
		{
			currentChar = text[position];
		}
	}

	void Lexer::SkipComment()
	{
		while (currentChar != '\n')
		{
			Advance();
		}

		Advance();
	}

	void Lexer::SkipWhitespace()
	{
		while (currentChar == ' ' || currentChar == '\t')
		{
			Advance();
		}
	}

	Token Lexer::NumberLiteral()
	{
		std::string value = "";

		while (currentChar != EOF && IsDigit(currentChar))
		{
			value += currentChar;
			Advance();
		}

		if (value == "0" && currentChar == 'b')
		{
			// todo.
			return std::move(Token{ TokenKind::LiteralBinary, value });
		}

		if (value == "0" && currentChar == 'o')
		{
			// todo.
			return std::move(Token{ TokenKind::LiteralOctal, value });
		}

		if (value == "0" && currentChar == 'x')
		{
			// todo.
			return std::move(Token{ TokenKind::LiteralHexa, value });
		}

		if (currentChar == 'f')
		{
			value += ".f";
			Advance();

			return std::move(Token{ TokenKind::LiteralFloat, value });
		}
		else if (currentChar == '.')
		{
			value += ".";
			Advance();

			while (currentChar != EOF && IsDigit(currentChar))
			{
				value += currentChar;
				Advance();
			}

			if (currentChar == 'f')
			{
				value += "f";
				Advance();

				return std::move(Token{ TokenKind::LiteralFloat, value });
			}

			return std::move(Token{ TokenKind::LiteralDouble, value });
		}

		return std::move(Token{ TokenKind::LiteralInteger, value });
	}

	Token Lexer::StringLiteral()
	{
		std::string value = "";
		value += currentChar;
		Advance();

		while (currentChar != EOF && currentChar != '"')
		{
			value += currentChar;
			Advance();
		}

		value += currentChar;
		Advance();

		return std::move(Token{ TokenKind::LiteralInteger, value });
	}

	Token Lexer::Identifier()
	{
		std::string value = "";

		while (currentChar != EOF && IsSymbolChar(currentChar))
		{
			value += currentChar;
			Advance();
		}

		if (g_TokenKindKeywordMap.contains(value))
		{
			return std::move(Token{ g_TokenKindKeywordMap.at(value), value });
		}

		return std::move(Token{ TokenKind::Identifier, value });
	}

	Token Lexer::NextToken()
	{
		while (currentChar != EOF)
		{
			switch (currentChar)
			{
			case ' ':
			{
				if (currentChar != '\n')
				{
					SkipWhitespace();
				}

				break;
			}
			case '#':
			{
				SkipComment();
				break;
			}
			case DIGIT:
			{
				return NumberLiteral();
			}
			case SYMBOL_START:
			{
				return Identifier();
			}
			case '"':
			{
				return StringLiteral();
			}
			case '\n':
			case '\t':
			{
				Advance();
				return std::move(Token{ TokenKind::Eol, "\n" });
			}
			case '=':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorEq, "==" });
				}
				else if (peekRes == '>')
				{
					Advance();
					return std::move(Token{ TokenKind::Follow, "=>" });
				}

				return std::move(Token{ TokenKind::OperatorAssign, "=" });
			}
			case '<':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorLe, "<=" });
				}
				else if (peekRes == '<')
				{
					Advance();
					return std::move(Token{ TokenKind::BitLeftShift, "<<" });
				}

				return std::move(Token{ TokenKind::OperatorLt, "<" });
			}
			case '>':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorGe, ">=" });
				}
				else if (peekRes == '>')
				{
					peekRes = Peek();
					Advance();

					if (peekRes == '>')
					{
						Advance();
						return std::move(Token{ TokenKind::BitUnsignedRightShift, ">>>" });
					}

					return std::move(Token{ TokenKind::BitRightShift, ">>" });
				}

				return std::move(Token{ TokenKind::OperatorGt, ">" });
			}
			case '+':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorAddAssign, "+=" });
				}

				return std::move(Token{ TokenKind::OperatorAdd, "+" });
			}
			case '-':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorSubAssign, "-=" });
				}
				else if (peekRes == '>')
				{
					Advance();
					return std::move(Token{ TokenKind::Arrow, "->" });
				}

				return std::move(Token{ TokenKind::OperatorSub, "-" });
			}
			case '*':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorMulAssign, "*=" });
				}
				else if (peekRes == '*')
				{
					peekRes = Peek();
					Advance();

					if (peekRes == '=')
					{
						Advance();
						return std::move(Token{ TokenKind::OperatorPowAssign, "**=" });
					}

					return std::move(Token{ TokenKind::OperatorPow, "**" });
				}

				return std::move(Token{ TokenKind::OperatorMul, "*" });
			}
			case '/':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorDivAssign, "/=" });
				}
				else if (peekRes == '/')
				{
					peekRes = Peek();
					Advance();

					if (peekRes == '=')
					{
						Advance();
						return std::move(Token{ TokenKind::OperatorRootAssign, "//=" });
					}

					return std::move(Token{ TokenKind::OperatorRoot, "//" });
				}

				return std::move(Token{ TokenKind::OperatorDiv, "/" });
			}
			case '%':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorModAssign, "%=" });
				}

				return std::move(Token{ TokenKind::OperatorMod, "%" });
			}
			case '&':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '&')
				{
					Advance();
					return std::move(Token{ TokenKind::LogicalAnd, "&&" });
				}

				throw std::move(Token{ TokenKind::BitAnd, "&" });
			}
			case '|':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '|')
				{
					Advance();
					return std::move(Token{ TokenKind::LogicalOr, "||" });
				}

				throw std::move(Token{ TokenKind::BitOr, "|" });
			}
			case '!':
			{
				char peekRes = Peek();
				Advance();

				if (peekRes == '=')
				{
					Advance();
					return std::move(Token{ TokenKind::OperatorNe, "!=" });
				}
				else if (peekRes == '#')
				{
					SkipComment(); // todo. Generate documentation instead
					break;
				}

				return std::move(Token{ TokenKind::LogicalNot, "!" });
			}
			case '~':
			{
				Advance();
				return std::move(Token{ TokenKind::BitNot, "!" });
			}
			case '^':
			{
				Advance();
				return std::move(Token{ TokenKind::BitXor, "!" });
			}
			case '@':
			{
				Advance();
				return std::move(Token{ TokenKind::At, "@" });
			}
			case '(':
			{
				Advance();
				return std::move(Token{ TokenKind::OpenParen, "(" });
			}
			case ')':
			{
				Advance();
				return std::move(Token{ TokenKind::CloseParen, ")" });
			}
			case '{':
			{
				Advance();
				return std::move(Token{ TokenKind::OpenBrace, "{" });
			}
			case '}':
			{
				Advance();
				return std::move(Token{ TokenKind::CloseBrace, "}" });
			}
			case '[':
			{
				Advance();
				return std::move(Token{ TokenKind::OpenBracket, "[" });
			}
			case ']':
			{
				Advance();
				return std::move(Token{ TokenKind::CloseBracket, "]" });
			}
			case '.':
			{
				char peekRes = Peek();
				Advance();

				if (Peek() == '.')
				{
					peekRes = Peek();
					Advance();

					if (peekRes == '=')
					{
						Advance();
						return std::move(Token{ TokenKind::RangeInclusive, "..=" });
					}

					return std::move(Token{ TokenKind::RangeExclusive, ".." });
				}

				return std::move(Token{ TokenKind::Dot, "." });
			}
			case ':':
			{
				Advance();
				return std::move(Token{ TokenKind::Colon, ":" });
			}
			case ',':
			{
				Advance();
				return std::move(Token{ TokenKind::Comma, "," });
			}
			case ';':
			{
				Advance();
				return std::move(Token{ TokenKind::Semicolon, ";" });
			}
			default:
			{
				break; // todo. error
			}
			}
		}

		return std::move(Token{ TokenKind::Eof, "" });
	}

	char Lexer::Peek()
	{
		size_t peekPosition = position + 1;

		if (peekPosition > text.length())
		{
			return EOF;
		}

		return text[peekPosition];
	}
}