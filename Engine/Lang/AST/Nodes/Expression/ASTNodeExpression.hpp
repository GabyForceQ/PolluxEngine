/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../../ASTNodeBase.hpp"
#include "ExpressionKind.hpp"

namespace Pollux::Lang
{
	class ASTNodeExpression final : public ASTNodeBase
	{
	public:
		explicit ASTNodeExpression(ExpressionKind kind) noexcept;

		void Accept(IASTNodeVisitor* pVisitor) override;

		ExpressionKind kind;
		
		ASTNodeExpression* pUnaryOp = nullptr;
		
		ASTNodeExpression* pBinaryOpLeft = nullptr;
		
		ASTNodeExpression* pBinaryOpRight = nullptr;
		
		ASTNodeType* pBinaryOpType = nullptr;
	};
}