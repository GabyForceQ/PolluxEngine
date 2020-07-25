/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ASTNodeEmptyStatement.hpp"

namespace Pollux::Lang
{
	ASTNodeEmptyStatement::ASTNodeEmptyStatement() noexcept
		:
		ASTNodeBase{ Token{ TokenKind::Undefined, "" } }
	{
	}

	void ASTNodeEmptyStatement::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}