/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../Tokenizer/Token.hpp"
#include "CompilerUnitFile.hpp"

namespace Pollux::Lang
{
	class Lexer;
	class SymbolTable;
	class Compiler;

	class CompilerUnit final
	{
	public:
		explicit CompilerUnit(Compiler* pCompiler) noexcept;

		std::unordered_map<std::string, Lexer*> pLexerMap;

		~CompilerUnit() = default;

		void tokenize();
		
		void parse();
		
		void parse_symbol_table();

		bool in_symbol_table(const std::string& symbol) const;

		uint64_t get_next_token_pos() const;

		Token get_token(uint64_t pos, bool movePos = false) const;

		Token get_curr_token() const;

		Token NextToken(uint64_t disp = 0ull) const;

		Token get_prev_token(uint64_t disp = 0ull) const;

		std::string get_header_unit() const;
		
		std::string get_source_unit() const;

		std::string get_name() const;
		
		std::string get_upper_name() const;
		
		std::string get_full_name() const;
		
		std::string get_full_upper_name() const;
		
		std::string get_symbol_name() const;

		void build_header();
		
		void build_source();

		bool is_main = false;
		
		std::stringstream source_unit;

	private:
		Compiler* pCompiler = nullptr;
		std::stringstream header_unit;
		std::deque<Token> tokens;
		std::unordered_map<std::string, Token> token_map;
		mutable uint64_t next_token_pos = 0;
		std::unordered_map<std::string, std::string> prototype_map;
		SymbolTable* symbol_table;
		std::unordered_map<std::string, CompilerUnitFile> file_map;
		std::unordered_map<std::string, std::string> str_map;
		std::string name;
		std::string upper_name;
		std::string full_name;
		std::string full_upper_name;
		std::string symbol_name;

		friend Compiler;
	};
}