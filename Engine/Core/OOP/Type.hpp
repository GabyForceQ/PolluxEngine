/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "OOPUtils.hpp"

namespace Pollux::Core
{
	class Type : public NonCopyableNorMovable<Type>
	{
	public:
		bool IsTypeOf(const type_t type) const noexcept;
		
		bool IsStringOf(const std::string& str) const noexcept;
		
		type_t GetTypeOf() const noexcept;
		
		std::string GetStringOf() const noexcept;
		
		std::vector<type_t> GetTypeOfVector() const noexcept;
		
		std::vector<std::string> GetStringOfVector() const noexcept;

	protected:
		void RegisterType(const std::string& str, const type_t type) noexcept;

	private:
		std::vector<type_t> typeOfVector;
		std::vector<std::string> stringOfVector;
	};
}