/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Solution.hpp"
#include "Project.hpp"

namespace Pollux::BuildSystem
{
    Solution::Solution(const std::vector<Project*>& pProjects)
        :
        pProjects{ pProjects }
    {
    }

    void Solution::SetProjectType(ProjectType projectType)
    {
        this->projectType = projectType;

        for (Project* pProject : pProjects)
        {
            pProject->SetProjectType(projectType);
        }
    }
}