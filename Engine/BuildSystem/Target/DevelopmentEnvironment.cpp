/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "DevelopmentEnvironment.hpp"

namespace Pollux::BuildSystem
{
	std::underlying_type_t<DevelopmentEnvironment> operator+(DevelopmentEnvironment self)
	{
		using T = std::underlying_type_t<DevelopmentEnvironment>;
		return static_cast<T>(self);
	}

	DevelopmentEnvironment operator|(DevelopmentEnvironment lhs, DevelopmentEnvironment rhs)
	{
		using T = std::underlying_type_t<DevelopmentEnvironment>;
		return static_cast<DevelopmentEnvironment>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}

	DevelopmentEnvironment& operator|=(DevelopmentEnvironment& lhs, DevelopmentEnvironment rhs)
	{
		lhs = lhs | rhs;
		return lhs;
	}

	DevelopmentEnvironment operator&(DevelopmentEnvironment lhs, DevelopmentEnvironment rhs)
	{
		using T = std::underlying_type_t<DevelopmentEnvironment>;
		return static_cast<DevelopmentEnvironment>(static_cast<T>(lhs) & static_cast<T>(rhs));
	}

	DevelopmentEnvironment& operator&=(DevelopmentEnvironment& lhs, DevelopmentEnvironment rhs)
	{
		lhs = lhs & rhs;
		return lhs;
	}

	const size_t g_DevelopmentEnvironmentCount = 2;
	const char* g_DevelopmentEnvironment_VS2019 = "DevelopmentEnvironment::VS2019";
	const char* g_DevelopmentEnvironment_Makefile = "DevelopmentEnvironment::Makefile";

	const std::map<const char*, DevelopmentEnvironment> g_DevelopmentEnvironmentMap
	{
		{ g_DevelopmentEnvironment_VS2019, DevelopmentEnvironment::VS2019 },
		{ g_DevelopmentEnvironment_Makefile, DevelopmentEnvironment::Makefile }
	};

	DevelopmentEnvironment DevelopmentEnvironmentToEnum(const char* developmentEnvironment)
	{
		if (g_DevelopmentEnvironmentMap.contains(developmentEnvironment))
		{
			return g_DevelopmentEnvironmentMap.at(developmentEnvironment);
		}

		throw std::runtime_error("Error (BuildSystem): DevelopmentEnvironment string is not valid.");
	}

	std::string ToString(const DevelopmentEnvironment developmentEnvironment)
	{
		switch (developmentEnvironment)
		{
		case DevelopmentEnvironment::VS2019: return g_DevelopmentEnvironment_VS2019;
		case DevelopmentEnvironment::Makefile: return g_DevelopmentEnvironment_Makefile;
		}

		return g_pEmptyString;
	}
}