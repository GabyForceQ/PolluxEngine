/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "CXXCompilerUtils.hpp"

namespace Pollux::Lang
{
	std::string CXXCompilerUtils::ToPrimitive(const std::string& pxType)
	{
		if (pxType == "Int")
		{
			return "int32_t";
		}
		else if (pxType == "Float")
		{
			return "float";
		}
		else if (pxType == "Double")
		{
			return "double";
		}
		else if (pxType == "Bool")
		{
			return "bool";
		}
		else if (pxType == "Unit")
		{
			return "void";
		}
		else if (pxType == "String")
		{
			return "std::string";
		}

		return "";
	}
}