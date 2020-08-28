/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "Scope/ScopeKindFlag.hpp"

namespace Pollux::Lang
{
	struct PxType;

	enum class PxTypeKind
	{
		Invalid,
		Unit,
		Bool,
		Int,
		ComptimeInt
	};

	struct PxTypeInt
	{
		uint32_t m_BitCount = 0u;
		bool m_bSigned = false;
	};

	struct PxValue
	{
		PxType* m_pType;

		PxValue(const PxValue& other) = delete;
	};

	struct PxType
	{
		PxTypeKind m_Kind = PxTypeKind::Invalid;
		std::string m_Name;

		/*union
		{
			PxTypeInt m_TypeInt;
		} m_Data;*/

		//PxType* m_PointerParent[2]; // [0 - var, 1 - val]
		PxValue* m_CachedConstNameVal = nullptr;
		size_t m_SizeInBits = 0_sz;

		std::string ToString() const
		{
			std::string res;

			switch (m_Kind)
			{
			case PxTypeKind::Invalid: res += "Invalid"; break;
			case PxTypeKind::Unit: res += "Unit"; break;
			case PxTypeKind::Bool: res += "Bool"; break;
			case PxTypeKind::Int: res += "Int"; break;
			case PxTypeKind::ComptimeInt: res += "ComptimeInt"; break;
			default: break;
			}

			return res;
		}
	};

	enum class PxContainerKind
	{
		ContainerKindUnit
	};

	enum class PxDeclKind
	{
		Invalid,
		Var,
		Val,
		Fun,
		Struct,
		Enum
	};

	struct PxDecl
	{
		PxDeclKind m_Kind = PxDeclKind::Invalid;

		std::string ToString() const
		{
			std::string res;

			switch (m_Kind)
			{
			case PxDeclKind::Invalid: res += "Invalid"; break;
			case PxDeclKind::Var: res += "Var"; break;
			case PxDeclKind::Val: res += "Val"; break;
			case PxDeclKind::Fun: res += "Fun"; break;
			case PxDeclKind::Struct: res += "Struct"; break;
			case PxDeclKind::Enum: res += "Enum"; break;
			default: break;
			}

			return res;
		}
	};

	struct PxSymbolTable;

	enum class PxAccessKind
	{
		Public,
		Private,
		Protected,
		Package,
		Internal
	};

	struct PxAccess
	{
		PxAccessKind m_Kind = PxAccessKind::Public;

		std::string ToString() const
		{
			std::string res;

			switch (m_Kind)
			{
			case PxAccessKind::Public: res += "Public"; break;
			case PxAccessKind::Private: res += "Private"; break;
			case PxAccessKind::Protected: res += "Protected"; break;
			case PxAccessKind::Package: res += "Package"; break;
			case PxAccessKind::Internal: res += "Internal"; break;
			default: break;
			}

			return res;
		}
	};

	enum class PxUsageKind
	{
		Runtime,
		Comptime,
		Anytime
	};

	struct PxUsage
	{
		PxUsageKind m_Kind = PxUsageKind::Anytime;

		std::string ToString() const
		{
			std::string res;

			switch (m_Kind)
			{
			case PxUsageKind::Runtime: res += "Runtime"; break;
			case PxUsageKind::Comptime: res += "Comptime"; break;
			case PxUsageKind::Anytime: res += "Anytime"; break;
			default: break;
			}

			return res;
		}
	};

	enum class PxScopeKind
	{
		Global,
		Fun,
		Struct
	};

	struct PxScope
	{
		PxScopeKind m_Kind = PxScopeKind::Global;
		PxUsage m_Usage;
		PxAccess m_Access;
		bool m_bInsideStruct = false;
		bool m_bInsideLoop = false;

		std::string ToString() const
		{
			std::string res;

			switch (m_Kind)
			{
			case PxScopeKind::Global: res += "Global"; break;
			case PxScopeKind::Fun: res += "Fun"; break;
			case PxScopeKind::Struct: res += "Struct"; break;
			default: break;
			}

			return res;
		}
	};

	struct PxSymbol
	{
		std::string m_Name;
		PxUsage m_Usage;
		PxScope m_Scope;
		PxDecl m_Decl;
		PxType m_Type;
		PxAccess m_Access;
		std::string m_BaseName;
		std::queue<std::string> m_ImplList;
		bool m_bExtern = false;
		bool m_bGeneric = false;
		PxSymbolTable* m_pSymbolTable = nullptr;

		// todo. add params and generic params
	};
	
	struct PxSymbolTable
	{
		PxScope m_Scope;
		std::vector<PxSymbol> m_Symbols;

		void Append(PxSymbolTable* pOther)
		{
			m_Symbols.insert(std::end(m_Symbols), std::begin(pOther->m_Symbols), std::end(pOther->m_Symbols));
		}
	};
}