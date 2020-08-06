/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../ASTNodeBase.hpp"

namespace Pollux::Lang
{
	class ASTNodeScope final : public ASTNodeBase
	{
	public:
		explicit ASTNodeScope() noexcept;

		void Accept(IASTNodeVisitor* pVisitor) override;

		void InsertStatement(ASTNodeBase* pStatement);

		const std::vector<ASTNodeBase*>& GetStatements() const noexcept;

	private:
		std::vector<ASTNodeBase*> pStatements;

		AST_FRIENDS_BODY
	};
}