/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "EngineBuilder/enginebuilderpch.hpp"

#include "EngineBuilderProject.hpp"

using namespace Pollux::BuildSystem;

namespace Pollux::EngineBuilder
{
    EngineBuilderProject::EngineBuilderProject() noexcept
    {
        name = "EngineBuilder";
        path = "EngineBuilder.vcxproj";
        pProjectFilters->path = "EngineBuilder.vcxproj.filters";
    }

    void EngineBuilderProject::ConfigureWin64(BuildConfiguration& config, const BuildTarget& target)
    {
        Project::ConfigureWin64(config, target);
    }

    void EngineBuilderProject::ConfigureAll(BuildConfiguration& config, const BuildTarget& target)
    {
        Project::ConfigureAll(config, target);

        config.buildOutputType = BuildOutputType::Executable;
        config.linkerInputLibraries.push_back("Engine.lib");
    }
}