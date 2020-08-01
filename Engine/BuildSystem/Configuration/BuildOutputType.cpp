/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildOutputType.hpp"

namespace Pollux::BuildSystem
{
	const size_t g_BuildOutputTypeCount = 6;
	const char* g_BuildOutputType_None = "BuildOutputType::None";
	const char* g_BuildOutputType_Makefile = "BuildOutputType::Makefile";
	const char* g_BuildOutputType_Executable = "BuildOutputType::Executable";
	const char* g_BuildOutputType_StaticLibrary = "BuildOutputType::StaticLibrary";
	const char* g_BuildOutputType_DynamicLibrary = "BuildOutputType::DynamicLibrary";
	const char* g_BuildOutputType_Utility = "BuildOutputType::Utility";

	const std::map<const char*, BuildOutputType> g_BuildOutputTypeMap
	{
		{ g_BuildOutputType_None, BuildOutputType::None },
		{ g_BuildOutputType_Makefile, BuildOutputType::Makefile },
		{ g_BuildOutputType_Executable, BuildOutputType::Executable },
		{ g_BuildOutputType_StaticLibrary, BuildOutputType::StaticLibrary },
		{ g_BuildOutputType_DynamicLibrary, BuildOutputType::DynamicLibrary },
		{ g_BuildOutputType_Utility, BuildOutputType::Utility }
	};

	BuildOutputType BuildOutputTypeToEnum(const char* buildOutputType)
	{
		if (g_BuildOutputTypeMap.contains(buildOutputType))
		{
			return g_BuildOutputTypeMap.at(buildOutputType);
		}

		throw std::runtime_error("Error (BuildSystem): BuildOutputType string is not valid.");
	}

	std::string ToString(const BuildOutputType buildOutputType)
	{
		switch (buildOutputType)
		{
		case BuildOutputType::None: return g_BuildOutputType_None;
		case BuildOutputType::Makefile: return g_BuildOutputType_Makefile;
		case BuildOutputType::Executable: return g_BuildOutputType_Executable;
		case BuildOutputType::StaticLibrary: return g_BuildOutputType_StaticLibrary;
		case BuildOutputType::DynamicLibrary: return g_BuildOutputType_DynamicLibrary;
		case BuildOutputType::Utility: return g_BuildOutputType_Utility;
		}

		return g_pEmptyString;
	}
}