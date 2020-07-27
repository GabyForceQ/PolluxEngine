/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "VSSolutionGenerator.hpp"
#include "Engine/BuildSystem/VisualStudio/Objects/VSSolution.hpp"
#include "Engine/BuildSystem/VisualStudio/Objects/VSProject.hpp"
#include "Engine/Core/Generic/GenericUtils.hpp"

namespace Pollux::BuildSystem
{
    std::string VSSolutionGenerator::Generate(Solution* pSolution)
    {
        auto pVSSolution = Core::Cast<VSSolution>(pSolution);

        std::string res = "Microsoft Visual Studio Solution File, Format Version 12.00\n"
            "# Visual Studio Version 16\n"
            "VisualStudioVersion = 16.0.29424.173\n"
            "MinimumVisualStudioVersion = 10.0.40219.1\n";

        for (Project* pProject : pSolution->pProjects)
        {
            auto pVSProject = Core::Cast<VSProject>(pProject);

            res += "Project(\"{" + pVSProject->type.ToString() + "}\") = \"" + pProject->name +
                "\", \"" + pProject->path + "\", \"{" + pVSProject->guid.ToString() + "}\"\n";

            if (!pVSProject->dependencies.empty())
            {
                res += "\tProjectSection(ProjectDependencies) = postProject\n";

                for (const auto& dependency : pVSProject->dependencies)
                {
                    res += "\t\t{" + dependency.ToString() + "} = {" + dependency.ToString() + "}\n";
                }

                res += "\tEndProjectSection\n";
            }

            res += "EndProject\n";
        }

        res += "Gloabl\n"
            "\tGlobalSection(SolutionConfigurationPlatforms) = preSolution\n";

        const std::vector<BuildConfiguration> configurations =
        {
            { "Debug", BuildPlatform::Windows, "x64", BuildConfigurationType::Debug },
            { "Release", BuildPlatform::Windows, "x64", BuildConfigurationType::Release },
            { "Retail", BuildPlatform::Windows, "x64", BuildConfigurationType::Retail },
        };

        for (const auto& configuration : configurations)
        {
            res += "\t\t" + configuration.name + "|" + configuration.architecture + " = " + configuration.name + "|" +
                configuration.architecture + "\n";
        }

        res += "\tEndGlobalSection\n"
            "\tGlobalSection(ProjectConfigurationPlatforms) = postSolution\n";

        for (Project* pProject : pSolution->pProjects)
        {
            auto pVSProject = Core::Cast<VSProject>(pProject);

            for (const auto& configuration : pProject->configurations)
            {
                res += "\t\t{" + pVSProject->guid.ToString() + "}." + configuration.name + "|" + configuration.architecture +
                    ".ActiveCfg = " + configuration.name + "|" + configuration.architecture + "\n";
                res += "\t\t{" + pVSProject->guid.ToString() + "}." + configuration.name + "|" + configuration.architecture +
                    ".Build.0 = " + configuration.name + "|" + configuration.architecture + "\n";
            }
        }

        res += "\tEndGlobalSection\n"
            "\tGlobalSection(SolutionProperties) = preSolution\n"
            "\t\tHideSolutionNode = FALSE\n"
            "\tEndGlobalSection\n"
            "EndGlobal\n";

        return std::move(res);
    }
}