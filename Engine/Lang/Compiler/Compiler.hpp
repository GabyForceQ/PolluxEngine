/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	class CompilerUnit;

	typedef std::unordered_map<std::string, CompilerUnit*> compiler_unit_map_t;

	class Compiler final
	{
	public:
		explicit Compiler(std::string srcFolderName = "") noexcept;

		~Compiler() = default;

		void Initialize(const std::deque<std::string> units);

		void Initialize();

		void BuildPrecompiledHeader();

		void BuildMain();

		void GetSymbolTable();

		void Compile();

		void Build();

		void Run();

		const std::deque<std::string> GetVersionIdentifiers() const;

		bool IsLocal() const noexcept;

		compiler_unit_map_t compilerUnitMap;

	private:
		void ParseSrcFolders(const std::filesystem::path& pathToShow, const int32_t level);

		std::string srcFolderName = "";
		bool bLocal = false;
	};
}