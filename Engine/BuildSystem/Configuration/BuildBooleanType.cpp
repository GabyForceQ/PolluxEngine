/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildBooleanType.hpp"

namespace Pollux::BuildSystem
{
	const size_t g_BuildBooleanTypeCount = 3;
	const char* g_BuildBooleanType_None = "BuildOutputType::None";
	const char* g_BuildBooleanType_True = "BuildOutputType::Makefile";
	const char* g_BuildBooleanType_False = "BuildOutputType::Executable";

	const std::map<const char*, BuildBooleanType> g_BuildBooleanTypeMap
	{
		{ g_BuildBooleanType_None, BuildBooleanType::None },
		{ g_BuildBooleanType_True, BuildBooleanType::True },
		{ g_BuildBooleanType_False, BuildBooleanType::False }
	};

	BuildBooleanType BuildBooleanTypeToEnum(const char* buildBooleanType)
	{
		if (g_BuildBooleanTypeMap.contains(buildBooleanType))
		{
			return g_BuildBooleanTypeMap.at(buildBooleanType);
		}

		throw std::runtime_error("Error (BuildSystem): BuildBooleanType string is not valid.");
	}

	std::string ToString(const BuildBooleanType buildBooleanType)
	{
		switch (buildBooleanType)
		{
		case BuildBooleanType::None: return g_BuildBooleanType_None;
		case BuildBooleanType::True: return g_BuildBooleanType_True;
		case BuildBooleanType::False: return g_BuildBooleanType_False;
		}

		return g_pEmptyString;
	}
}