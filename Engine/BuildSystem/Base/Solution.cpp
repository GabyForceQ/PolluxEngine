/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Solution.hpp"
#include "Project.hpp"
#include "Engine/BuildSystem/BuildSystem.hpp"

namespace Pollux::BuildSystem
{
    Solution::Solution(const std::string& path) noexcept
        :
        path{ path }
    {
    }

    void Solution::Implement(BuildSystem* pBuildSystem)
    {
        for (type_t i = 0u; i < g_BuildOptimizationCount; i++)
        {
            const BuildOptimization platform = static_cast<BuildOptimization>(i);

            if (pBuildSystem->configurationMap.contains(platform))
            {
                ConfigureWin64(*pBuildSystem->configurationMap[platform], pBuildSystem->target);
                ConfigureAll(*pBuildSystem->globalConfiguration, pBuildSystem->target);
                PostConfig(*pBuildSystem->globalConfiguration,
                    *pBuildSystem->configurationMap[platform], pBuildSystem->target);
            }
        }
    }

    const std::string& Solution::GetPath() const noexcept
    {
        return path;
    }
    
    void Solution::ConfigureWin64(BuildConfiguration& config, const BuildTarget& target)
    {
        for (Project* pProject : pProjects)
        {
            pProject->ConfigureWin64(config, target);
        }
    }

    void Solution::ConfigureAll(BuildConfiguration& config, const BuildTarget& target)
    {
        for (Project* pProject : pProjects)
        {
            pProject->ConfigureAll(config, target);
        }
    }

    void Solution::PostConfig(BuildConfiguration& globalConfig, BuildConfiguration& config, const BuildTarget& target)
    {
        for (Project* pProject : pProjects)
        {
            pProject->PostConfig(globalConfig, config, target);
        }
    }
}