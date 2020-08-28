/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../ASTNodeBase.hpp"
#include "../../../PxTypes.hpp"
#include "../../../Scope/ScopeKindFlag.hpp"

namespace Pollux::Lang
{
	class ASTNodeContainerDecl final : public ASTNodeBase
	{
	public:
		explicit ASTNodeContainerDecl() noexcept;

		void Accept(IASTNodeVisitor* pVisitor) override;

	private:
		//std::vector<ASTNodeBase*> m_pFields;
		//std::vector<ASTNodeBase*> m_pDecls;
		ScopeKindFlag m_Kind;
		std::vector<PxSymbol> m_Symbols;

		AST_FRIENDS_BODY
	};
}