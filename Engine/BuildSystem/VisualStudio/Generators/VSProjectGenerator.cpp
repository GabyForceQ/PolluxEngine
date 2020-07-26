/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "VSProjectGenerator.hpp"
#include "Engine/BuildSystem/VisualStudio/Objects/VSProject.hpp"
#include "Engine/Core/Generic/GenericUtils.hpp"

namespace Pollux::BuildSystem
{
    std::string VSProjectGenerator::Generate(Project* pProject)
    {
        auto pVSProject = Core::Cast<VSProject>(pProject);

        std::string res = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
            "<Project DefaultTargets=\"Build\" ToolsVersion=\"16.0\" "
            "xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\n";

        res += "  <ItemGroup Label=\"ProjectConfigurations\">\n";

        for (const auto& configuration : pProject->configurations)
        {
            res += "    <ProjectConfiguration Include=\"" + configuration.name + "|" + configuration.architecture + "\">\n";
            res += "      <Configuration>" + configuration.name + "</Configuration>\n";
            res += "      <Platform>" + configuration.architecture + "</Platform>\n";
            res += "    </ProjectConfiguration>\n";
        }

        res += "  </ItemGroup>\n";

        res += "  <PropertyGroup Label=\"Globals\">\n";
        res += "    <ProjectGuid>{" + pVSProject->guid.ToString() + "}</ProjectGuid>\n";
        res += "    <DefaultLanguage>en-US</DefaultLanguage>";
        res += "    <RootNamespace>Pollux</RootNamespace>\n";
        res += "    <ProjectName>" + pProject->name + "</ProjectName>\n";
        res += "    <WindowsTargetPlatformVersion>10.0.18362.0</WindowsTargetPlatformVersion>\n";
        res += "  </PropertyGroup>\n";

        res += "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" />\n";

        for (const auto& configuration : pProject->configurations)
        {
            res += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='" + configuration.name + "|" +
                configuration.architecture + "'\" Label=\"Configuration\">\n";
            res += "    <ConfigurationType>Application</ConfigurationType>\n";
            res += "    <PlatformToolset>v142</PlatformToolset>\n";

            switch (configuration.type)
            {
            case BuildConfigurationType::Debug:
            {
                res += "    <UseDebugLibraries>true</UseDebugLibraries>\n";
                break;
            }
            case BuildConfigurationType::Release:
            {
                res += "    <UseDebugLibraries>false</UseDebugLibraries>\n";
                break;
            }
            case BuildConfigurationType::Retail:
            {
                res += "    <UseDebugLibraries>false</UseDebugLibraries>\n";
                res += "    <WholeProgramOptimization>true</WholeProgramOptimization>\n";
                break;
            }
            default:
                break;
            }
            
            res += "    <CharacterSet>MultiByte</CharacterSet>\n";
            res += "  </PropertyGroup>\n";
        }

        res += "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />\n";
        res += "  <ImportGroup Label=\"ExtensionSettings\">\n";
        res += "  </ImportGroup>\n";
        res += "  <ImportGroup Label=\"PropertySheets\">\n";
        res += "  <ImportGroup Label=\"Shared\">\n";
        res += "  </ImportGroup>\n";

        for (const auto& configuration : pProject->configurations)
        {
            res += "  <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)'=='" +
                configuration.name + "|" + configuration.architecture + "'\">\n";
            res += "    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\""
                "exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />\n";
            res += "  </ImportGroup>\n";
        }

        res += "  <PropertyGroup Label=\"UserMacros\" />\n";

        res += "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" />\n";
        res += "  <ImportGroup Label=\"ExtensionTargets\">\n";
        res += "  </ImportGroup>\n";

        res += "</Project>";

        return std::move(res);
    }
}