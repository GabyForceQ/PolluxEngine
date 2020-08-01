/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class BuildPlatform : type_t
	{
		None = 0x0000,
		Windows = 0x0001,
		Linux = 0x0002,
		Android = 0x0004
	};

	std::underlying_type_t<BuildPlatform> operator+(BuildPlatform self);

	BuildPlatform operator|(BuildPlatform lhs, BuildPlatform rhs);

	BuildPlatform& operator|=(BuildPlatform& lhs, BuildPlatform rhs);

	BuildPlatform operator&(BuildPlatform lhs, BuildPlatform rhs);

	BuildPlatform& operator&=(BuildPlatform& lhs, BuildPlatform rhs);

	extern const size_t g_BuildPlatformCount;

	extern const char* g_BuildPlatform_None;

	extern const char* g_BuildPlatform_Windows;
	
	extern const char* g_BuildPlatform_Linux;
	
	extern const char* g_BuildPlatform_Android;

	extern const std::map<const char*, BuildPlatform> g_BuildPlatformMap;

	BuildPlatform BuildPlatformToEnum(const char* buildPlatform);

	std::string ToString(const BuildPlatform buildPlatform);
}