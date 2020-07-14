/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Type.hpp"
#include "../Generic/GenericUtils.hpp"

namespace Pollux::Core
{
    bool Type::IsTypeOf(const type_t type) const noexcept
    {
        return std::find(typeOfVector.begin(), typeOfVector.end(), type) != typeOfVector.end();
    }

    bool Type::IsStringOf(const std::string& str) const noexcept
    {
        return std::find(stringOfVector.begin(), stringOfVector.end(), str) != stringOfVector.end();
    }

    type_t Type::GetTypeOf() const noexcept
    {
        return *(typeOfVector.end() - 1);
    }

    std::string Type::GetStringOf() const noexcept
    {
        return *(stringOfVector.end() - 1);
    }

    std::vector<type_t> Type::GetTypeOfVector() const noexcept
    {
        return typeOfVector;
    }

    std::vector<std::string> Type::GetStringOfVector() const noexcept
    {
        return stringOfVector;
    }

    void Type::RegisterType(const std::string& str, const type_t type) noexcept
    {
        if (Contains(typeOfVector, type) || Contains(stringOfVector, str))
        {
            // todo. warn message
            return;
        }

        typeOfVector.emplace_back(type);
        stringOfVector.emplace_back(str);
    }
}