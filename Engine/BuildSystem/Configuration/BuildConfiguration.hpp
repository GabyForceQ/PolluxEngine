/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "BuildBooleanType.hpp"
#include "../Target/BuildOptimization.hpp"

namespace Pollux::BuildSystem
{
	struct BuildConfiguration final
	{
		BuildConfiguration() = delete;

		BuildConfiguration(BuildOptimization optimization) noexcept;

		BuildConfiguration& operator=(const BuildConfiguration& rhs);

		const BuildOptimization optimization;
		
		std::string projectName;
		
		std::string projectPath;
		
		std::vector<std::string> preprocessorDefinitions;
		
		bool bUsePrecompiledHeaders = false;

		std::string precompiledHeaderName;

		bool bUseDebugLibraries = false;

		BuildBooleanType wholeProgramOptimization = BuildBooleanType::None;

		bool bLinkIncremental = false;

		BuildBooleanType functionLevelLinking = BuildBooleanType::None;

		bool bIntrinsicFunctions = false;

		bool bBufferSecurityCheck = false;

		bool bStringPooling = false;



		bool bGenerateDebugInformation = false;

		bool bOptimizeReferences = false;

		bool bEnableCOMDATFolding = false;
	};
}