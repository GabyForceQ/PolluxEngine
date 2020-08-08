/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ScopeKindFlag.hpp"

namespace Pollux::Lang
{
	std::underlying_type_t<ScopeKindFlag> operator+(ScopeKindFlag self)
	{
		using T = std::underlying_type_t<ScopeKindFlag>;
		return static_cast<T>(self);
	}

	ScopeKindFlag operator|(ScopeKindFlag lhs, ScopeKindFlag rhs)
	{
		using T = std::underlying_type_t<ScopeKindFlag>;
		return static_cast<ScopeKindFlag>(static_cast<T>(lhs) | static_cast<T>(rhs));
	}

	ScopeKindFlag& operator|=(ScopeKindFlag& lhs, ScopeKindFlag rhs)
	{
		lhs = lhs | rhs;
		return lhs;
	}

	ScopeKindFlag operator&(ScopeKindFlag lhs, ScopeKindFlag rhs)
	{
		using T = std::underlying_type_t<ScopeKindFlag>;
		return static_cast<ScopeKindFlag>(static_cast<T>(lhs) & static_cast<T>(rhs));
	}

	ScopeKindFlag& operator&=(ScopeKindFlag& lhs, ScopeKindFlag rhs)
	{
		lhs = lhs & rhs;
		return lhs;
	}

	const size_t g_ScopeKindFlagCount = 4;
	const std::underlying_type_t<ScopeKindFlag> g_ScopeKindFlagMin = +ScopeKindFlag::Fun;
	const std::underlying_type_t<ScopeKindFlag> g_ScopeKindFlagMax = +ScopeKindFlag::IfElse;

	const std::underlying_type_t<ScopeKindFlag> g_ScopeKindFlagFlagArray[2] =
	{
		+ScopeKindFlag::Fun,
		+ScopeKindFlag::IfElse
	};
	
	const std::string g_ScopeKindFlag_FieldName_Global = "Global";
	const std::string g_ScopeKindFlag_FieldName_Fun = "Fun";
	const std::string g_ScopeKindFlag_FieldName_IfElse = "IfElse";
	const std::string g_ScopeKindFlag_FieldFullName_Global = "ScopeKindFlag.Global";
	const std::string g_ScopeKindFlag_FieldFullName_Fun = "ScopeKindFlag.Fun";
	const std::string g_ScopeKindFlag_FieldFullName_IfElse = "ScopeKindFlag.IfElse";

	const std::map<std::string, ScopeKindFlag> g_ScopeKindFlag_FieldNameMap
	{
		{ g_ScopeKindFlag_FieldName_Global, ScopeKindFlag::Global },
		{ g_ScopeKindFlag_FieldName_Fun, ScopeKindFlag::Fun },
		{ g_ScopeKindFlag_FieldName_IfElse, ScopeKindFlag::IfElse }
	};

	const std::map<std::string, ScopeKindFlag> g_ScopeKindFlag_FieldFullNameMap
	{
		{ g_ScopeKindFlag_FieldFullName_Global, ScopeKindFlag::Global },
		{ g_ScopeKindFlag_FieldFullName_Fun, ScopeKindFlag::Fun },
		{ g_ScopeKindFlag_FieldFullName_IfElse, ScopeKindFlag::IfElse }
	};

	ScopeKindFlag ScopeKindFlagToEnum(const std::string& scopeKindFlag)
	{
		if (g_ScopeKindFlag_FieldNameMap.contains(scopeKindFlag) ||
			g_ScopeKindFlag_FieldFullNameMap.contains(scopeKindFlag))
		{
			return g_ScopeKindFlag_FieldNameMap.at(scopeKindFlag);
		}

		throw std::runtime_error("Error (Lang): ScopeKindFlag string is not valid.");
	}

	std::string FieldNameToString(const ScopeKindFlag scopeKindFlag)
	{
		switch (scopeKindFlag)
		{
		case ScopeKindFlag::Global: return g_ScopeKindFlag_FieldName_Global;
		case ScopeKindFlag::Fun: return g_ScopeKindFlag_FieldName_Fun;
		case ScopeKindFlag::IfElse: return g_ScopeKindFlag_FieldName_IfElse;
		}

		return g_pEmptyString;
	}

	std::string FieldFullNameToString(const ScopeKindFlag scopeKindFlag)
	{
		switch (scopeKindFlag)
		{
		case ScopeKindFlag::Global: return g_ScopeKindFlag_FieldFullName_Global;
		case ScopeKindFlag::Fun: return g_ScopeKindFlag_FieldFullName_Fun;
		case ScopeKindFlag::IfElse: return g_ScopeKindFlag_FieldFullName_IfElse;
		}

		return g_pEmptyString;
	}
}