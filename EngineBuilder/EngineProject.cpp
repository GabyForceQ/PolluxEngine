/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "EngineBuilder/enginebuilderpch.hpp"

#include "EngineProject.hpp"

using namespace Pollux::BuildSystem;

namespace Pollux::EngineBuilder
{
    EngineProject::EngineProject() noexcept
    {
        name = "Engine";
        path = "Engine.vcxproj";
    }

    void EngineProject::ConfigureWin64(BuildConfiguration& config, const BuildTarget& target)
    {
    }

    void EngineProject::ConfigureAll(BuildConfiguration& config, const BuildTarget& target)
    {
    }
}