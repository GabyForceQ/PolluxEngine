/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Project.hpp"
#include "Engine/BuildSystem/VisualStudio/Objects/VSProject.hpp"
#include "Engine/BuildSystem/BuildSystem.hpp"

#include "Engine/BuildSystem/VisualStudio/Filters/VSProjectFilters.hpp"

namespace Pollux::BuildSystem
{
	Project::Project() noexcept
		:
		pBuildSystem{ new BuildSystem() },
		pProjectFilters{ new ProjectFilters(this) }
	{
	}

	const std::string& Project::GetName() const noexcept
	{
		return name;
	}

	const std::string& Project::GetPath() const noexcept
	{
		return path;
	}

	const std::string& Project::GetGeneratedCode() const noexcept
	{
		return generatedCode;
	}

	void Project::ConfigureWin64(BuildConfiguration& config, const BuildTarget& target)
	{
		config.preprocessorDefinitions.push_back("POLLUX_SYSTEM_WINDOWS");
		config.preprocessorDefinitions.push_back("WIN32_LEAN_AND_MEAN");
		config.preprocessorDefinitions.push_back("_CRT_SECURE_NO_WARNINGS");
		config.preprocessorDefinitions.push_back("_SCL_SECURE_NO_WARNINGS");
		config.preprocessorDefinitions.push_back("_WINSOCKAPI_");
		config.preprocessorDefinitions.push_back("NOMINMAX");
		config.preprocessorDefinitions.push_back("STRICT");
		config.preprocessorDefinitions.push_back("_USE_MATH_DEFINES");
		config.preprocessorDefinitions.push_back("POLLUX_DRIVER_VULKAN");
	}

	void Project::ConfigureAll(BuildConfiguration& config, const BuildTarget& target)
	{
		config.bUsePrecompiledHeaders = true;
		config.precompiledHeaderName = name + "PCH";
		config.preprocessorDefinitions.push_back("POLLUX_PLATFORM_X64");
		config.includeDirectories.push_back("..\\..\\..\\extern\\singleinclude");

		switch (target.optimization)
		{
		case BuildOptimization::Debug:
		{
			config.preprocessorDefinitions.push_back("POLLUX_TARGET_DEBUG");
			
			break;
		}
		case BuildOptimization::Release:
		{
			config.preprocessorDefinitions.push_back("POLLUX_TARGET_RELEASE");
			
			break;
		}
		case BuildOptimization::Retail:
		{
			config.preprocessorDefinitions.push_back("POLLUX_TARGET_RETAIL");			
			
			break;
		}
		}

		switch (target.optimization)
		{
		case BuildOptimization::Debug:
		{
			config.preprocessorDefinitions.push_back("_DEBUG");
			config.bUseDebugLibraries = true;
			config.wholeProgramOptimization = BuildBooleanType::None;
			config.bLinkIncremental = true;
			config.functionLevelLinking = BuildBooleanType::None;
			config.bIntrinsicFunctions = false;
			config.bBufferSecurityCheck = true;
			config.bStringPooling = false;

			config.bGenerateDebugInformation = true;
			config.bOptimizeReferences = false;
			config.bEnableCOMDATFolding = false;

			break;
		}
		case BuildOptimization::Release:
		case BuildOptimization::Retail:
		{
			config.preprocessorDefinitions.push_back("NDEBUG");
			config.bUseDebugLibraries = false;
			config.wholeProgramOptimization = BuildBooleanType::True;
			config.bLinkIncremental = false;
			config.functionLevelLinking = BuildBooleanType::True;
			config.bIntrinsicFunctions = true;
			config.bBufferSecurityCheck = false;
			config.bStringPooling = true;

			config.bGenerateDebugInformation = false;
			config.bOptimizeReferences = true;
			config.bEnableCOMDATFolding = true;

			break;
		}
		}
	}

	void Project::Initialize(BuildSystem* pBuildSystem)
	{
		pBuildSystem->globalConfiguration->projectName = name;
		pBuildSystem->globalConfiguration->projectPath = path;

		for (auto& config : pBuildSystem->configurationMap)
		{
			config.second->projectName = name;
			config.second->projectPath = path;
		}
	}

	void Project::PostConfig(BuildConfiguration& globalConfig, BuildConfiguration& config, const BuildTarget& target)
	{
		config.bUsePrecompiledHeaders = globalConfig.bUsePrecompiledHeaders;
		config.precompiledHeaderName = globalConfig.precompiledHeaderName;
	}
}