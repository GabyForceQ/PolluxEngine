/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class BuildOptimization : type_t
	{
		None = 0x0000,
		Debug = 0x0001,
		Release = 0x0002,
		Retail = 0x0004
	};

	std::underlying_type_t<BuildOptimization> operator+(BuildOptimization self);

	BuildOptimization operator|(BuildOptimization lhs, BuildOptimization rhs);

	BuildOptimization& operator|=(BuildOptimization& lhs, BuildOptimization rhs);

	BuildOptimization operator&(BuildOptimization lhs, BuildOptimization rhs);

	BuildOptimization& operator&=(BuildOptimization& lhs, BuildOptimization rhs);

	extern const size_t g_BuildOptimizationCount;

	extern const std::underlying_type_t<BuildOptimization> g_BuildOptimizationMin;

	extern const std::underlying_type_t<BuildOptimization> g_BuildOptimizationMax;

	extern const std::underlying_type_t<BuildOptimization> g_BuildOptimizationFlagArray[3];

	extern const char* g_BuildOptimization_None;

	extern const char* g_BuildOptimization_Debug;

	extern const char* g_BuildOptimization_Release;
	
	extern const char* g_BuildOptimization_Retail;

	extern const std::map<const char*, BuildOptimization> g_BuildOptimizationMap;

	BuildOptimization BuildOptimizationToEnum(const char* buildOptimization);

	std::string ToString(const BuildOptimization buildOptimization);
}