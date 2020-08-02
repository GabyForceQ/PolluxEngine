/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "FileManager.hpp"

namespace Pollux::Core
{
	std::vector<std::string> FileManager::GetFilePaths(const std::string& fromPath, const std::string& extension,
		const std::string& startWith, const std::vector<std::string>& excludeList)
	{
		std::vector<std::string> res;

		if (extension == "")
		{
			for (auto& file : std::filesystem::recursive_directory_iterator(fromPath))
			{
				bool shouldInclude = true;

				for (auto& exclude : excludeList)
				{
					if (exclude == file.path().filename())
					{
						shouldInclude = false;
						break;
					}
				}

				if (shouldInclude)
				{
					res.push_back(startWith + file.path().string());
				}
			}
		}
		else
		{
			for (auto& file : std::filesystem::recursive_directory_iterator(fromPath))
			{
				if (file.path().extension() == extension)
				{
					bool shouldInclude = true;

					for (auto& exclude : excludeList)
					{
						if (exclude == file.path().filename())
						{
							shouldInclude = false;
							break;
						}
					}

					if (shouldInclude)
					{
						res.push_back(startWith + file.path().string());
					}
				}
			}
		}

		return res;
	}
}