/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "AstNodeContainerDecl.hpp"

namespace Pollux::Lang
{
	ASTNodeContainerDecl::ASTNodeContainerDecl() noexcept
		:
		ASTNodeBase{ Token::Empty() }
	{
		RegisterType("ASTNodeContainerDecl", +ASTNodeKind::ASTNodeContainerDecl);
	}

	void ASTNodeContainerDecl::Accept(IASTNodeVisitor* pVisitor)
	{
		return pVisitor->Visit(this);
	}
}