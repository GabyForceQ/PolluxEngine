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
    EditorProject::EditorProject()
    {
        name = "Editor";
        path = "Editor.vcxproj";
    }

    void EditorProject::ConfigureWin64()
    {
        configurations.push_back({ "Debug", BuildPlatform::Windows, "x64", BuildConfigurationType::Debug });
        configurations.push_back({ "Release", BuildPlatform::Windows, "x64", BuildConfigurationType::Release });
        configurations.push_back({ "Retail", BuildPlatform::Windows, "x64", BuildConfigurationType::Retail });
    }
}