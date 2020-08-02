/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Core
{
	class FileManager final
	{
	public:
		static std::vector<std::string> GetFilePaths(const std::string& fromPath, const std::string& extension = "",
			const std::string& startWith = "", const std::vector<std::string>& excludeList = {});
	};
}