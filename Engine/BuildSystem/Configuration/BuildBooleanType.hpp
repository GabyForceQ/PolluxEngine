/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class BuildBooleanType
	{
		None,
		True,
		False
	};

	extern const size_t g_BuildBooleanTypeCount;

	extern const char* g_BuildBooleanType_None;

	extern const char* g_BuildBooleanType_True;

	extern const char* g_BuildBooleanType_False;

	extern const std::map<const char*, BuildBooleanType> g_BuildBooleanTypeMap;

	BuildBooleanType BuildBooleanTypeToEnum(const char* buildBooleanType);

	std::string ToString(const BuildBooleanType buildBooleanType);
}