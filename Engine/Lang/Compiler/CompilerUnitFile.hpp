/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	class CompilerUnitFile final
	{
	public:
		explicit CompilerUnitFile(std::string relativePath, std::string absolutePath, std::string name) noexcept;

		~CompilerUnitFile() = default;

		const std::string relativePath;

		const std::string absolutePath;

		const std::string name;
	};
}