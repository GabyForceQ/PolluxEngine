/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildOptimization.hpp"

namespace Pollux::BuildSystem
{
	std::underlying_type_t<BuildOptimization> operator+(BuildOptimization self)
	{
		using T = std::underlying_type_t<BuildOptimization>;
		return static_cast<T>(self);
	}

	BuildOptimization operator|(BuildOptimization lhs, BuildOptimization rhs)
	{
		using T = std::underlying_type_t<BuildOptimization>;
		return static_cast<BuildOptimization>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}

	BuildOptimization& operator|=(BuildOptimization& lhs, BuildOptimization rhs)
	{
		lhs = lhs | rhs;
		return lhs;
	}

	BuildOptimization operator&(BuildOptimization lhs, BuildOptimization rhs)
	{
		using T = std::underlying_type_t<BuildOptimization>;
		return static_cast<BuildOptimization>(static_cast<T>(lhs) & static_cast<T>(rhs));
	}

	BuildOptimization& operator&=(BuildOptimization& lhs, BuildOptimization rhs)
	{
		lhs = lhs & rhs;
		return lhs;
	}

	const size_t g_BuildOptimizationCount = 4;
	const std::underlying_type_t<BuildOptimization> g_BuildOptimizationMin = +BuildOptimization::Debug;
	const std::underlying_type_t<BuildOptimization> g_BuildOptimizationMax = +BuildOptimization::Retail;
	const std::underlying_type_t<BuildOptimization> g_BuildOptimizationFlagArray[3] = { 0x0001, 0x0002, 0x0004 };
	const char* g_BuildOptimization_None = "BuildOptimization::None";
	const char* g_BuildOptimization_Debug = "BuildOptimization::Debug";
	const char* g_BuildOptimization_Release = "BuildOptimization::Release";
	const char* g_BuildOptimization_Retail = "BuildOptimization::Retail";

	const std::map<const char*, BuildOptimization> g_BuildOptimizationMap
	{
		{ g_BuildOptimization_None, BuildOptimization::None },
		{ g_BuildOptimization_Debug, BuildOptimization::Debug },
		{ g_BuildOptimization_Release, BuildOptimization::Release },
		{ g_BuildOptimization_Retail, BuildOptimization::Retail }
	};

	BuildOptimization BuildOptimizationToEnum(const char* buildOptimization)
	{
		if (g_BuildOptimizationMap.contains(buildOptimization))
		{
			return g_BuildOptimizationMap.at(buildOptimization);
		}

		throw std::runtime_error("Error (BuildSystem): BuildOptimization string is not valid.");
	}

	std::string ToString(const BuildOptimization buildOptimization)
	{
		switch (buildOptimization)
		{
		case BuildOptimization::None: return g_BuildOptimization_None;
		case BuildOptimization::Debug: return g_BuildOptimization_Debug;
		case BuildOptimization::Release: return g_BuildOptimization_Release;
		case BuildOptimization::Retail: return g_BuildOptimization_Retail;
		}

		return g_pEmptyString;
	}
}