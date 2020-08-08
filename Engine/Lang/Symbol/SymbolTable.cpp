/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "SymbolTable.hpp"
#include "../AST/Nodes/Symbol/ASTNodeTypeSymbol.hpp"

namespace Pollux::Lang
{
	SymbolTable::SymbolTable() noexcept
	{
		Insert(new ASTNodeTypeSymbol("int", SymbolKind::PrimitiveType,
			new ASTNodeTypeSymbol("int", SymbolKind::Undefined, nullptr)));
		Insert(new ASTNodeTypeSymbol("float", SymbolKind::PrimitiveType,
			new ASTNodeTypeSymbol("float", SymbolKind::Undefined, nullptr)));
		Insert(new ASTNodeTypeSymbol("bool", SymbolKind::PrimitiveType,
			new ASTNodeTypeSymbol("bool", SymbolKind::Undefined, nullptr)));
		Insert(new ASTNodeTypeSymbol("string", SymbolKind::PrimitiveType,
			new ASTNodeTypeSymbol("string", SymbolKind::Undefined, nullptr)));
	}

	void SymbolTable::Insert(ASTNodeSymbol* pSymbol)
	{
		pSymbolMap[pSymbol->GetName()] = pSymbol;
	}

	ASTNodeSymbol* SymbolTable::LookUp(const std::string& name)
	{
		if (!pSymbolMap.contains(name))
		{
			return nullptr;
		}

		return pSymbolMap.at(name);
	}

	std::string SymbolTable::ToString()
	{
		std::string res = "Symbols: {";

		for (const auto& symbol : pSymbolMap)
		{
			res += "\n\tname: " + symbol.second->GetName()
				+ ", type: " + symbol.second->GetPTypeSymbol()->GetName()
				+ ", kind: " + Lang::ToString(symbol.second->GetSymbolKind())
				+ ", content: " + symbol.second->content;
		}

		res += "\n}\n";
		return res;
	}
}