/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "CompilerUnit.hpp"
#include "Compiler.hpp"
#include "../Tokenizer/Lexer.hpp"
#include "../Symbol/SymbolTable.hpp"

namespace Pollux::Lang
{
    CompilerUnit::CompilerUnit(Compiler* pCompiler) noexcept
        :
        pCompiler{ pCompiler }
    {
    }

	void CompilerUnit::tokenize()
	{
		if (pCompiler->IsLocal())
		{
			for (auto const& s : str_map)
			{
				std::fstream f;
				f.open("temp_cu.px", std::ios::out);
				f << s.second;
				f.close();

				pLexerMap["temp_cu"] = new Lexer("temp_cu.px");
				auto lexer = pLexerMap["temp_cu"];
				Token tok = lexer->NextToken();
				
				while (tok.kind != TokenKind::Eof)
				{
					token_map.insert({ "temp_cu", tok });
					tokens.push_back(tok);
					tok = lexer->NextToken();
				}
			}
		}
		else
		{
			for (auto const& f : file_map)
			{
				pLexerMap[f.second.name] = new Lexer("../../../lang_test/" + f.second.absolutePath);
				auto lexer = pLexerMap[f.second.name];
				Token tok = lexer->NextToken();
				
				while (tok.kind != TokenKind::Eof)
				{
					token_map.insert({ f.second.name, tok });
					tokens.push_back(tok);
					tok = lexer->NextToken();
				}
			}
		}
	}

	void CompilerUnit::parse()
	{
		size_t i = 0, size = token_map.size();
		//gen_node_unit(this);
		Token tok = NextToken();
		bool ok = true;
		
		while (ok)
		{
			switch (tok.kind)
			{
			case TokenKind::Undefined:
			{
				ok = false;
				throw std::runtime_error("Error!");
				break;
			}
			case TokenKind::Eof:
			{
				if (++i == size)
				{
					ok = false;
				}
				else
				{
					tok = NextToken();
				}
				break;
			}
			case TokenKind::Identifier:
			{
				//std::string symbolName = tok.kind;
				tok = NextToken();
				
				if (tok.kind == TokenKind::OperatorAssign)
				{ // Init or operator=
					// TODO. Check if symbol has operator= overloaded
					//auto node = parse_init_statement(this, symbolName);
					//m_SourceUnit << node;
				}
				//else if (tok.kind == TokenKind::QuestionMark)
				//{ // Nullcheck
				//
				//}
				else if (tok.kind == TokenKind::OpenParen)
				{ // Function call

				}
				tok = NextToken();
			}
			case TokenKind::KeywordUse:
			case TokenKind::Eol:
			default:
			{
				tok = NextToken();
				break;
			}
			}
		}
	}

	void CompilerUnit::parse_symbol_table()
	{
		//m_HeaderUnit << "class " << m_UpperName
		//	<< "__ final {\npublic: explicit " << m_Name << "() = default;\n";

		uint32_t scopeHierarchy = 0;
		for (uint64_t i = 0; i < tokens.size(); i++)
		{
			if (tokens[i].kind == TokenKind::OpenBrace)
			{
				scopeHierarchy++;
			}
			
			if (tokens[i].kind == TokenKind::CloseBrace)
			{
				scopeHierarchy--;
			}
			
			if (tokens[i].kind == TokenKind::Identifier)
			{
				if (tokens[++(++i)].kind == TokenKind::KeywordFun)
				{
					uint64_t start_i = i - 2; //
					std::string name_ = tokens[i - 2].value;
					std::string type_ = "";
					
					do
					{
						if (//tokens[++i].value == TokenType::KEYWORD_PRIMITIVE &&
							tokens[i - 1].kind == TokenKind::Colon
							&& tokens[i - 2].kind == TokenKind::CloseParen)
						{
							type_ = tokens[i].value;
						}
					} while (tokens[i].kind != TokenKind::OperatorAssign
						&& tokens[i].kind != TokenKind::OpenBrace
						&& tokens[i].kind != TokenKind::Identifier);

					if (type_ == "")
					{
						type_ = "Unit";
					}

					if (name_ != "")
					{
						//symbol_table->scope->symbol_map[name_] = std::make_shared<Symbol>(SymbolID::FUN, name_, type_);
					}

					//header_unit << parse_fun_prototype_for_header(shared_from_this(), start_i)->code_gen;
					i--;
				}
			}
		}

		//std::cout << "\n\n" << symbol_table->scope->serialized();
	}

	bool CompilerUnit::in_symbol_table(const std::string& symbol) const
	{
		if (symbol_table != nullptr)
		{
			//if (symbol_table->scope->symbol_map.find(symbol) !=
			//	symbol_table->scope->symbol_map.end())
			//{
			//	return true;
			//}
		}

		return false;
	}

	uint64_t CompilerUnit::get_next_token_pos() const
	{
		return next_token_pos;
	}

	Token CompilerUnit::get_token(uint64_t pos, bool movePos) const
	{
		if (pos < tokens.size())
		{
			if (movePos)
			{
				next_token_pos = pos + 1;
			}

			return tokens[pos];
		}

		throw std::runtime_error("Overflow!");
	}

	Token CompilerUnit::get_curr_token() const
	{
		return tokens[next_token_pos - 1];
	}

	Token CompilerUnit::NextToken(uint64_t disp) const
	{
		if (next_token_pos + disp < tokens.size())
		{
			next_token_pos++;
			return tokens[next_token_pos + disp - 1];
		}

		Token token{ TokenKind::Eof, "" };
		return std::move(token);
	}

	Token CompilerUnit::get_prev_token(uint64_t disp) const
	{
		if (next_token_pos - disp > 0)
		{
			next_token_pos--;
			return tokens[next_token_pos - disp - 1];
		}

		throw std::runtime_error("Underflow!");
	}

	std::string CompilerUnit::get_header_unit() const
	{
		return header_unit.str();
	}

	std::string CompilerUnit::get_source_unit() const
	{
		return source_unit.str();
	}

	std::string CompilerUnit::get_name() const
	{
		return name;
	}

	std::string CompilerUnit::get_upper_name() const
	{
		return upper_name;
	}

	std::string CompilerUnit::get_full_name() const
	{
		return full_name;
	}

	std::string CompilerUnit::get_full_upper_name() const
	{
		return full_upper_name;
	}

	std::string CompilerUnit::get_symbol_name() const
	{
		return symbol_name;
	}

	void CompilerUnit::build_header()
	{
		std::fstream f;
		f.open("..\\..\\..\\lang_gen\\UNIT_" + upper_name + ".HPP", std::ios::out);

		f << "#ifdef _MSC_VER\n#pragma once\n#endif\n#ifndef " << full_upper_name
			<< "HPP__\n#define " << full_upper_name << "HPP__\n"
			<< "#include<pollux/EnginePackage.hpp>\n#include\"PROTOTYPES.HPP\"\n";

		f << "class " << full_upper_name << " final{\npublic:\nexplicit " << full_upper_name
			<< "()=default;\n~" << full_upper_name << "()=default;\n";

		f << header_unit.str();
		//f << code_gen.m_HeaderCode;

		f << "};\n#endif\n";
		f.close();
	}

	void CompilerUnit::build_source()
	{
		std::fstream f;
		f.open("..\\..\\..\\lang_gen\\UNIT_" + upper_name + ".CPP", std::ios::out);

		f << "#include\"LOCALPCH.HPP\"\n#include\"UNIT_" << upper_name << ".HPP\"\n";
		f << source_unit.str();

		f.close();
	}
}