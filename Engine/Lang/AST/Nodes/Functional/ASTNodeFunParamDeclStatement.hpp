/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../ASTNodeBase.hpp"

namespace Pollux::Lang
{
	class ASTNodeFunParamDeclStatement final : public ASTNodeBase
	{
	public:
		ASTNodeFunParamDeclStatement() noexcept;

		void Accept(IASTNodeVisitor* pVisitor) override;

		std::deque<ASTNodeDeclHolder*> pDeclHolders;

		AST_FRIENDS_BODY
	};
}