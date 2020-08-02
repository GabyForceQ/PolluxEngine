/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildPlatform.hpp"

namespace Pollux::BuildSystem
{
	std::underlying_type_t<BuildPlatform> operator+(BuildPlatform self)
	{
		using T = std::underlying_type_t<BuildPlatform>;
		return static_cast<T>(self);
	}

	BuildPlatform operator|(BuildPlatform lhs, BuildPlatform rhs)
	{
		using T = std::underlying_type_t<BuildPlatform>;
		return static_cast<BuildPlatform>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}

	BuildPlatform& operator|=(BuildPlatform& lhs, BuildPlatform rhs)
	{
		lhs = lhs | rhs;
		return lhs;
	}

	BuildPlatform operator&(BuildPlatform lhs, BuildPlatform rhs)
	{
		using T = std::underlying_type_t<BuildPlatform>;
		return static_cast<BuildPlatform>(static_cast<T>(lhs) & static_cast<T>(rhs));
	}

	BuildPlatform& operator&=(BuildPlatform& lhs, BuildPlatform rhs)
	{
		lhs = lhs & rhs;
		return lhs;
	}

	const size_t g_BuildPlatformCount = 4;
	const char* g_BuildPlatform_None = "BuildPlatform::None";
	const char* g_BuildPlatform_Windows = "BuildPlatform::Windows";
	const char* g_BuildPlatform_Linux = "BuildPlatform::Linux";
	const char* g_BuildPlatform_Android = "BuildPlatform::Android";

	const std::map<const char*, BuildPlatform> g_BuildPlatformMap
	{
		{ g_BuildPlatform_None, BuildPlatform::None },
		{ g_BuildPlatform_Windows, BuildPlatform::Windows },
		{ g_BuildPlatform_Linux, BuildPlatform::Linux },
		{ g_BuildPlatform_Android, BuildPlatform::Android }
	};

	BuildPlatform BuildPlatformToEnum(const char* buildPlatform)
	{
		if (g_BuildPlatformMap.contains(buildPlatform))
		{
			return g_BuildPlatformMap.at(buildPlatform);
		}

		throw std::runtime_error("Error (BuildSystem): BuildPlatform string is not valid.");
	}

	std::string ToString(const BuildPlatform buildPlatform)
	{
		switch (buildPlatform)
		{
		case BuildPlatform::None: return g_BuildPlatform_None;
		case BuildPlatform::Windows: return g_BuildPlatform_Windows;
		case BuildPlatform::Linux: return g_BuildPlatform_Linux;
		case BuildPlatform::Android: return g_BuildPlatform_Android;
		}

		return g_pEmptyString;
	}
}