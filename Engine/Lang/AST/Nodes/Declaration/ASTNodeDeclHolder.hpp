/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../ASTNodeBase.hpp"

namespace Pollux::Lang
{
	class ASTNodeDeclHolder final : public ASTNodeBase
	{
	public:
		ASTNodeDeclHolder() noexcept;

		void Accept(IASTNodeVisitor* pVisitor) override;

		ASTNodeType* pType = nullptr;

		ASTNodeAssign* pAssignment = nullptr;

		bool bAutoDeduction = true;

		bool bComptimeEval = false;
	};
}