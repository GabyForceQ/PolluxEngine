/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "BuildConfiguration.hpp"

namespace Pollux::BuildSystem
{
    BuildConfiguration::BuildConfiguration(BuildOptimization optimization) noexcept
        :
        optimization{ optimization }
    {
    }

    BuildConfiguration& BuildConfiguration::operator=(const BuildConfiguration& rhs)
    {
        projectName = rhs.projectName;
        projectPath = rhs.projectPath;
        preprocessorDefinitions = rhs.preprocessorDefinitions;
        bUsePrecompiledHeaders = rhs.bUsePrecompiledHeaders;
        precompiledHeaderName = rhs.precompiledHeaderName;
        bUseDebugLibraries = rhs.bUseDebugLibraries;
        wholeProgramOptimization = rhs.wholeProgramOptimization;
        bLinkIncremental = rhs.bLinkIncremental;
        functionLevelLinking = rhs.functionLevelLinking;
        bIntrinsicFunctions = rhs.bIntrinsicFunctions;
        bBufferSecurityCheck = rhs.bBufferSecurityCheck;
        bStringPooling = rhs.bStringPooling;

        bGenerateDebugInformation = rhs.bGenerateDebugInformation;
        bOptimizeReferences = rhs.bOptimizeReferences;
        bEnableCOMDATFolding = rhs.bEnableCOMDATFolding;

        return *this;
    }
}
