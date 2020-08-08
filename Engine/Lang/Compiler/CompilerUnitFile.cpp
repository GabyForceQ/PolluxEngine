/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "CompilerUnitFile.hpp"

namespace Pollux::Lang
{
	CompilerUnitFile::CompilerUnitFile(std::string relativePath, std::string absolutePath, std::string name) noexcept
		:
		relativePath{ std::move(relativePath) },
		absolutePath{ std::move(absolutePath) },
		name{ std::move(name) }
	{
	}
}