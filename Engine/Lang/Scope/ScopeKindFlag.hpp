/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Lang
{
	enum class ScopeKindFlag : type_t
	{
		Global = 0x0000,
		Fun = 0x0001,
		IfElse = 0x0002
	};

	std::underlying_type_t<ScopeKindFlag> operator+(ScopeKindFlag self);

	ScopeKindFlag operator|(ScopeKindFlag lhs, ScopeKindFlag rhs);

	ScopeKindFlag& operator|=(ScopeKindFlag& lhs, ScopeKindFlag rhs);

	ScopeKindFlag operator&(ScopeKindFlag lhs, ScopeKindFlag rhs);

	ScopeKindFlag& operator&=(ScopeKindFlag& lhs, ScopeKindFlag rhs);

	extern const size_t g_ScopeKindFlagCount;

	extern const std::underlying_type_t<ScopeKindFlag> g_ScopeKindFlagMin;

	extern const std::underlying_type_t<ScopeKindFlag> g_ScopeKindFlagMax;

	extern const std::underlying_type_t<ScopeKindFlag> g_ScopeKindFlagFlagArray[2];

	extern const std::string g_ScopeKindFlag_FieldName_Global;

	extern const std::string g_ScopeKindFlag_FieldName_Fun;

	extern const std::string g_ScopeKindFlag_FieldName_IfElse;

	extern const std::string g_ScopeKindFlag_FieldFullName_Global;

	extern const std::string g_ScopeKindFlag_FieldFullName_Fun;

	extern const std::string g_ScopeKindFlag_FieldFullName_IfElse;

	extern const std::map<std::string, ScopeKindFlag> g_ScopeKindFlag_FieldNameMap;

	extern const std::map<std::string, ScopeKindFlag> g_ScopeKindFlag_FieldFullNameMap;

	ScopeKindFlag ScopeKindFlagToEnum(const std::string& scopeKindFlag);

	std::string FieldNameToString(const ScopeKindFlag scopeKindFlag);

	std::string FieldFullNameToString(const ScopeKindFlag scopeKindFlag);
}