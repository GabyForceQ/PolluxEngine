/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../ASTNodeBase.hpp"

namespace Pollux::Lang
{
	class ASTNodeReturn final : public ASTNodeBase
	{
	public:
		ASTNodeReturn() noexcept;

		void Accept(IASTNodeVisitor* pVisitor) override;

	private:
		ASTNodeType* pReturnType = nullptr;

		ASTNodeExpression* pExpression = nullptr;

		ASTNodeFun* pFunction = nullptr;

		AST_FRIENDS_BODY
	};
}