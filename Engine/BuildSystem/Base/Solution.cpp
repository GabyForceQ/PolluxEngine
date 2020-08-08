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
#include "Engine/BuildSystem/Interfaces/IProjectFilterGenerator.hpp"
#include "Engine/BuildSystem/Filters/ProjectFilters.hpp"
#include "Engine/Core/Storage/FileManager.hpp"

namespace Pollux::BuildSystem
{
    Solution::Solution(const std::string& path) noexcept
        :
        path{ path }
    {
    }

    void Solution::Implement(BuildSystem* pBuildSystem, IProjectGenerator* pProjectGenerator,
        IProjectFiltersGenerator* pProjectFiltersGenerator)
    {
        this->pBuildSystem = pBuildSystem;
        this->pProjectGenerator = pProjectGenerator;

        for (const type_t optimizationFlag : g_BuildOptimizationFlagArray)
        {
            const BuildOptimization optimization = static_cast<BuildOptimization>(optimizationFlag);
            pBuildSystem->target.currentOptimization = optimization;

            if (pBuildSystem->configurationMap.contains(optimization))
            {
                ConfigureAll(*pBuildSystem->configurationMap[optimization], pBuildSystem->target);
                ConfigureWin64(*pBuildSystem->configurationMap[optimization], pBuildSystem->target);
                //PostConfig(*pBuildSystem->globalConfiguration,
                //    *pBuildSystem->configurationMap[optimization], pBuildSystem->target);
            }
        }

        for (Project* pProject : pProjects)
        {
            std::string pchName;
            bool bUsePch = false;

            for (const type_t optimizationFlag : g_BuildOptimizationFlagArray)
            {
                const BuildOptimization optimization = static_cast<BuildOptimization>(optimizationFlag);
                pBuildSystem->target.currentOptimization = optimization;

                if (pBuildSystem->configurationMap.contains(optimization))
                {
                    pProject->ConfigureAll(*pBuildSystem->configurationMap[optimization], pBuildSystem->target);
                    pProject->ConfigureWin64(*pBuildSystem->configurationMap[optimization], pBuildSystem->target);
                    //pProject->PostConfig(*pBuildSystem->globalConfiguration,
                    //    *pBuildSystem->configurationMap[optimization], pBuildSystem->target);
                    
                    *pProject->pBuildSystem = *pBuildSystem;

                    if (pBuildSystem->configurationMap[optimization]->bUsePrecompiledHeaders)
                    {
                        bUsePch = true;
                        pchName = pBuildSystem->configurationMap[optimization]->precompiledHeaderName;
                    }
                }
            }

            if (bUsePch)
            {
                pProject->pProjectFilters->headerFiles = Core::FileManager::GetFilePaths(
                    pProject->name, ".hpp", "..\\..\\..\\", { pchName + ".hpp" });
                pProject->pProjectFilters->sourceFiles = Core::FileManager::GetFilePaths(
                    pProject->name, ".cpp", "..\\..\\..\\", { pchName + ".cpp" });
            }
            else
            {
                pProject->pProjectFilters->headerFiles = Core::FileManager::GetFilePaths(
                    pProject->name, ".hpp", "..\\..\\..\\");
                pProject->pProjectFilters->sourceFiles = Core::FileManager::GetFilePaths(
                    pProject->name, ".cpp", "..\\..\\..\\");
            }

            pProjectGenerator->Generate(pProject);

            if (bUsePch)
            {
                pProject->pProjectFilters->headerFiles.push_back(pProject->name + "\\" + pchName + ".hpp");
                pProject->pProjectFilters->sourceFiles.push_back(pProject->name + "\\" + pchName + ".cpp");
            }

            pProjectFiltersGenerator->Generate(pProject->pProjectFilters);

            pBuildSystem->Reset();
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

    void Solution::PostConfig(BuildConfiguration& config, const BuildTarget& target)
    {
    }
}