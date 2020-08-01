/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	enum class DevelopmentEnvironment : type_t
	{
		VS2019 = 0x0001,
		Makefile = 0x0002
	};

	std::underlying_type_t<DevelopmentEnvironment> operator+(DevelopmentEnvironment self);

	DevelopmentEnvironment operator|(DevelopmentEnvironment lhs, DevelopmentEnvironment rhs);

	DevelopmentEnvironment& operator|=(DevelopmentEnvironment& lhs, DevelopmentEnvironment rhs);

	DevelopmentEnvironment operator&(DevelopmentEnvironment lhs, DevelopmentEnvironment rhs);

	DevelopmentEnvironment& operator&=(DevelopmentEnvironment& lhs, DevelopmentEnvironment rhs);

	extern const size_t g_DevelopmentEnvironmentCount;

	extern const char* g_DevelopmentEnvironment_VS2019;

	extern const char* g_DevelopmentEnvironment_Makefile;

	extern const std::map<const char*, DevelopmentEnvironment> g_DevelopmentEnvironmentMap;

	DevelopmentEnvironment DevelopmentEnvironmentToEnum(const char* developmentEnvironment);

	std::string ToString(const DevelopmentEnvironment developmentEnvironment);
}