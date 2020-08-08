/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "VSProjectFiltersGenerator.hpp"
#include "Engine/BuildSystem/VisualStudio/Filters/VSProjectFilters.hpp"
#include "Engine/BuildSystem/Base/Project.hpp"
#include "Engine/BuildSystem/BuildSystem.hpp"

#define GLOBAL_CONFIG pProjectFilters->pProject->pBuildSystem->configurationMap.at(BuildOptimization::Debug)

namespace Pollux::BuildSystem
{
	void VSProjectFiltersGenerator::Generate(ProjectFilters* pProjectFilters)
	{
		std::string& res = pProjectFilters->generatedCode;
		VSProjectFilters* pVSProjectFilters = pProjectFilters->pVSProjectFilters;

		auto IsPchFile = [=](const std::string& path) -> bool
		{
			const std::string& pchName = GLOBAL_CONFIG->precompiledHeaderName;
			const size_t found = path.find_last_of("\\");
			const std::string fileName = path.substr(found + 1, path.length() - 1);
			return fileName == pchName + ".cpp" || fileName == pchName + ".hpp";
		};

		res = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
			"<Project DefaultTargets=\"Build\" ToolsVersion=\"16.0\" "
			"xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n"
			"  <ItemGroup>\n";

		for (const std::string& path : pProjectFilters->sourceFiles)
		{
			std::string basePath = GetFilterBasePath(path, pProjectFilters->pProject->GetName());

			if (basePath != "")
			{
				pProjectFilters->filters.insert(basePath);
			}

			res += "    <ClCompile Include=\"" + path + "\">\n";

			if (!GLOBAL_CONFIG->bUsePrecompiledHeaders)
			{
				res += "      <Filter>" + basePath + "</Filter>\n";
			}
			else if (!IsPchFile(path))
			{
				res += "      <Filter>" + basePath + "</Filter>\n";
			}

			res += "    </ClCompile>\n";
		}

		res += "  </ItemGroup>\n"
			"  <ItemGroup>\n";

		for (const std::string& path : pProjectFilters->headerFiles)
		{
			std::string basePath = GetFilterBasePath(path, pProjectFilters->pProject->GetName());

			if (basePath != "")
			{
				pProjectFilters->filters.insert(basePath);
			}

			res += "    <ClInclude Include=\"" + path + "\">\n";

			if (!GLOBAL_CONFIG->bUsePrecompiledHeaders)
			{
				res += "      <Filter>" + basePath + "</Filter>\n";
			}
			else if (!IsPchFile(path))
			{
				res += "      <Filter>" + basePath + "</Filter>\n";
			}

			res += "    </ClInclude>\n";
		}

		res += "  </ItemGroup>\n"
			"  <ItemGroup>\n";

		for (const std::string& path : pProjectFilters->filters)
		{
			VSGuid guid = VSGuid::Create();
			
			pVSProjectFilters->idGuids.emplace_back(guid);

			res += "    <Filter Include=\"" + path + "\">\n"
				"      <UniqueIdentifier>" + guid.ToString() + "</UniqueIdentifier>\n"
				"    </Filter>\n";
		}

		res += "  </ItemGroup>\n"
			"</Project>";
	}

	std::string VSProjectFiltersGenerator::GetFilterBasePath(const std::string& fullPath, const std::string& projectName)
	{
		std::string res = fullPath;
		
		size_t found = res.find_first_of(projectName);
		res = res.substr(found + projectName.size() + 1, res.length() - 1);

		found = res.find_last_of("\\");
		res = res.substr(0, found);

		if (res.find('.') != std::string::npos)
		{
			res = "";
		}

		return std::move(res);
	}
}