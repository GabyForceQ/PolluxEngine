/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class BuildOutputType
	{
		None,
		Makefile,
		Executable,
		StaticLibrary,
		DynamicLibrary,
		Utility,
	};

	extern const size_t g_BuildOutputTypeCount;

	extern const char* g_BuildOutputType_None;

	extern const char* g_BuildOutputType_Makefile;
	
	extern const char* g_BuildOutputType_Executable;
	
	extern const char* g_BuildOutputType_StaticLibrary;
	
	extern const char* g_BuildOutputType_DynamicLibrary;
	
	extern const char* g_BuildOutputType_Utility;
	
	extern const std::map<const char*, BuildOutputType> g_BuildOutputTypeMap;

	BuildOutputType BuildPlatformToEnum(const char* buildOutputType);

	std::string ToString(const BuildOutputType buildOutputType);
}