/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Editor/EditorPCH.hpp"

std::string PrintSymbolTable(Lang::PxSymbolTable* pSymbolTable, std::string previousName = "")
{
	std::string res;

	for (const auto& symbol : pSymbolTable->m_Symbols)
	{
		Lang::PxSymbolTable* pChildSymbolTable = symbol.m_pSymbolTable;
		const std::string nameStr = (previousName == "") ? symbol.m_Name : previousName + "." + symbol.m_Name;
		const std::string externStrs = (symbol.m_bExtern) ? "true" : "false";
		const std::string genericStr = (symbol.m_bGeneric) ? "true" : "false";
		const std::string insideStr = symbol.m_Scope.m_bInsideStruct ? ", inside(struct)" : "";

		res += "Symbol\n{\n\tname: " + nameStr +
			"\n\tusage: " + symbol.m_Usage.ToString() +
			"\n\tscope: " + symbol.m_Scope.ToString() + insideStr +
			"\n\tdecl: " + symbol.m_Decl.ToString() +
			"\n\taccess: " + symbol.m_Access.ToString() +
			"\n\textern: " + externStrs +
			"\n\tgeneric: " + genericStr;

		switch (symbol.m_Decl.m_Kind)
		{
		case::Lang::PxDeclKind::Var:
		case::Lang::PxDeclKind::Val:
		case Lang::PxDeclKind::Fun:
		{
			res += "\n\ttype: " + symbol.m_Type.ToString();
			break;
		}
		case Lang::PxDeclKind::Struct:
		{
			std::string superStr = (symbol.m_BaseName != "") ? symbol.m_BaseName : "None";
			res += "\n\tsuper: " + superStr;

			//res += "\n\timpl: " + symbol.m_ImplList.ToString();
			
			break;
		}
		default: break;
		}
			
		res += "\n}\n";

		if (pChildSymbolTable != nullptr)
		{
			if (previousName == "")
			{
				res += PrintSymbolTable(pChildSymbolTable, symbol.m_Name);
			}
			else
			{
				res += PrintSymbolTable(pChildSymbolTable, previousName + "." + symbol.m_Name);
			}
		}
	}

	return res;
}

int32_t main(int32_t argc, char** argv)
{
	std::fstream f;
	f.open("Demo.px", std::ios::in);

	std::string code((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

	Lang::Lexer* pLexer = new Lang::Lexer(code);
	Lang::Parser* pParser = new Lang::Parser(pLexer);
	Lang::ASTNodeBase* pAST = pParser->Parse();

	std::cout << PrintSymbolTable(pParser->m_pUnitSymbolTable) << "\n";

	//Lang::SemanticAnalyser* pSemanticAnalyser = new Lang::SemanticAnalyser();
	//pAST->Accept(pSemanticAnalyser);
	//
	//Lang::CXXCodegen* pCXXCodegen = new Lang::CXXCodegen(pSemanticAnalyser->pSymbolTable);
	//pAST->Accept(pCXXCodegen);
	
	//std::cout << "\n\nCXX_CODEGEN:\n------------\n" << pCXXCodegen->GetGeneratedCode() << "\n------------\n";

	//SAFE_DELETE(pCXXCodegen);
	//SAFE_DELETE(pSemanticAnalyser);
	SAFE_DELETE(pParser);
	SAFE_DELETE(pLexer);

	f.close();
	return 0;
}