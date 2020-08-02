/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Solution.hpp"
#include "Project.hpp"
#include "Engine/BuildSystem/BuildSystem.hpp"
#include "Engine/BuildSystem/Interfaces/IProjectGenerator.hpp"

namespace Pollux::BuildSystem
{
    Solution::Solution(const std::string& path) noexcept
        :
        path{ path }
    {
    }

    void Solution::Implement(BuildSystem* pBuildSystem, IProjectGenerator* pProjectGenerator)
    {
        this->pBuildSystem = pBuildSystem;
        this->pProjectGenerator = pProjectGenerator;

        for (const type_t optimizationFlag : g_BuildOptimizationFlagArray)
        {
            const BuildOptimization optimization = static_cast<BuildOptimization>(optimizationFlag);

            ConfigureWin64(*pBuildSystem->configurationMap[optimization], pBuildSystem->target);
            ConfigureAll(*pBuildSystem->globalConfiguration, pBuildSystem->target);
            PostConfig(*pBuildSystem->globalConfiguration,
                *pBuildSystem->configurationMap[optimization], pBuildSystem->target);
        }

        for (Project* pProject : pProjects)
        {
            for (const type_t optimizationFlag : g_BuildOptimizationFlagArray)
            {
                const BuildOptimization optimization = static_cast<BuildOptimization>(optimizationFlag);

                if (pBuildSystem->configurationMap.contains(optimization))
                {
                    pProject->ConfigureWin64(*pBuildSystem->configurationMap[optimization], pBuildSystem->target);
                    pProject->ConfigureAll(*pBuildSystem->globalConfiguration, pBuildSystem->target);
                    pProject->PostConfig(*pBuildSystem->globalConfiguration,
                        *pBuildSystem->configurationMap[optimization], pBuildSystem->target);
                    *pProject->pBuildSystem = *pBuildSystem;
                    pProjectGenerator->Generate(pProject);
                }
            }
        }
    }

    const std::string& Solution::GetPath() const noexcept
    {
        return path;
    }
    
    void Solution::ConfigureWin64(BuildConfiguration& config, const BuildTarget& target)
    {
    }

    void Solution::ConfigureAll(BuildConfiguration& config, const BuildTarget& target)
    {
    }

    void Solution::PostConfig(BuildConfiguration& globalConfig, BuildConfiguration& config, const BuildTarget& target)
    {
    }
}