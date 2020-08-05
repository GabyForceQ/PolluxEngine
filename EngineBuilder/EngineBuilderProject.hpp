/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::EngineBuilder
{
    class EngineBuilderProject final : public BuildSystem::Project
    {
    public:
        EngineBuilderProject() noexcept;

    private:
        virtual void ConfigureWin64(BuildConfiguration& config, const BuildTarget& target) override;
        virtual void ConfigureAll(BuildConfiguration& config, const BuildTarget& target) override;
    };
}