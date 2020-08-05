/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ProjectFilters.hpp"

namespace Pollux::BuildSystem
{
    ProjectFilters::ProjectFilters(Project* pProject) noexcept
        :
        pProject{ pProject }
    {
    }

    const std::string& ProjectFilters::GetPath() const noexcept
    {
        return path;
    }

    const std::vector<std::string>& ProjectFilters::GetHeaderFiles() const noexcept
    {
        return headerFiles;
    }

    const std::vector<std::string>& ProjectFilters::GetSourceFiles() const noexcept
    {
        return sourceFiles;
    }

    const std::set<std::string>& ProjectFilters::GetFilters() const noexcept
    {
        return filters;
    }

    const std::string& ProjectFilters::GetGeneratedCode() const noexcept
    {
        return generatedCode;
    }
}