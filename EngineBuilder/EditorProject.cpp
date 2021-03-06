/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "EngineBuilder/enginebuilderpch.hpp"

#include "EditorProject.hpp"

using namespace Pollux::BuildSystem;

namespace Pollux::EngineBuilder
{
    EditorProject::EditorProject() noexcept
    {
        name = "Editor";
        path = "Editor.vcxproj";
        pProjectFilters->path = "Editor.vcxproj.filters";
    }

    void EditorProject::ConfigureWin64(BuildConfiguration& config, const BuildTarget& target)
    {
        Project::ConfigureWin64(config, target);
    }

    void EditorProject::ConfigureAll(BuildConfiguration& config, const BuildTarget& target)
    {
        Project::ConfigureAll(config, target);

        config.buildOutputType = BuildOutputType::Executable;
    }
}