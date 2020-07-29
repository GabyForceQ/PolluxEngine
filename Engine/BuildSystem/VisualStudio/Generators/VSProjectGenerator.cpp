/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "VSProjectGenerator.hpp"
#include "Engine/BuildSystem/Base/Project.hpp"
#include "Engine/BuildSystem/VisualStudio/Objects/VSProject.hpp"

namespace Pollux::BuildSystem
{
    std::string VSProjectGenerator::Generate(Project* pProject)
    {
        auto pVSProject = pProject->pVSProject;

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
        res += "    <VCProjectVersion>16.0</VCProjectVersion>\n";
        res += "    <Keyword>Win32Proj</Keyword>\n";
        res += "    <ProjectGuid>{" + pVSProject->guid.ToString() + "}</ProjectGuid>\n";
        res += "    <DefaultLanguage>en-US</DefaultLanguage>\n";
        res += "    <RootNamespace>" + pProject->name + "</RootNamespace>\n";
        res += "    <ProjectName>" + pProject->name + "</ProjectName>\n";
        res += "    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>\n";
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
                res += "    <WholeProgramOptimization>true</WholeProgramOptimization>\n";
                break;
            }
            case BuildConfigurationType::Retail:
            {
                res += "    <UseDebugLibraries>false</UseDebugLibraries>\n";
                res += "    <WholeProgramOptimization>true</WholeProgramOptimization>\n";
                break;
            }
            default:
                break; // todo. error
            }
            
            res += "    <PreferredToolArchitecture>x64</PreferredToolArchitecture>\n";
            res += "    <CharacterSet>MultiByte</CharacterSet>\n";
            res += "  </PropertyGroup>\n";
        }

        res += "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\"/>\n";
        res += "  <ImportGroup Label=\"ExtensionSettings\">\n";
        res += "  </ImportGroup>\n";
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

        res += "  <PropertyGroup Label=\"UserMacros\"/>\n";

        for (const auto& configuration : pProject->configurations)
        {
            res += "  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='" +
                configuration.name + "|" + configuration.architecture + "'\">\n";

            switch (configuration.type)
            {
            case BuildConfigurationType::Debug:
            {
                res += "    <LinkIncremental>true</LinkIncremental>\n";
                break;
            }
            case BuildConfigurationType::Release:
            {
                res += "    <LinkIncremental>false</LinkIncremental>\n";
                break;
            }
            case BuildConfigurationType::Retail:
            {
                res += "    <LinkIncremental>false</LinkIncremental>\n";
                break;
            }
            default:
                break; // todo. error
            }

            res += "  </PropertyGroup>\n";
        }

        for (const auto& configuration : pProject->configurations)
        {
            res += "  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)'=='" +
                configuration.name + "|" + configuration.architecture + "'\">\n";
            res += "    <ClCompile>\n";
            res += "      <WarningLevel>Level3</WarningLevel>\n";
            res += "      <SDLCheck>true</SDLCheck>\n";
            res += "      <ConformanceMode>true</ConformanceMode>\n";
            res += "      <AdditionalOptions>/Zc:__cplusplus</AdditionalOptions>\n";
            res += "      <ProgramDatabaseFileName>..\\..\\Temp\\Obj\\Win64_VS2019\\" +
                pProject->name + "\\" + configuration.name + "\\" + pProject->name +
                configuration.name + "Compiler.pdb</ProgramDatabaseFileName>\n";

            if (pProject->bUsePrecompiledHeaders)
            {
                res += "      <PrecompiledHeader>Use</PrecompiledHeader>\n";
                res += "      <PrecompiledHeaderFile>" + pProject->precompiledHeaderName +
                    ".hpp</PrecompiledHeaderFile>\n";
                res += "      <PrecompiledHeaderOutputFile>..\\..\\Temp\\Obj\\Win64_VS2019\\" +
                    pProject->name + "\\" + configuration.name + "\\" + pProject->name +
                    ".pch</PrecompiledHeaderOutputFile>\n";
            }
            else
            {
                res += "      <PrecompiledHeader>NotUsing</PrecompiledHeader>\n";
            }

            switch (configuration.type)
            {
            case BuildConfigurationType::Debug:
            {
                // Do not add this to Debug because /ZI and /Gy- or /Gy command line options are incompatible 
                //res += "        <FunctionLevelLinking>false</FunctionLevelLinking>\n";
                
                res += "        <IntrinsicFunctions>false</IntrinsicFunctions>\n";
                res += "        <RuntimeLibrary>MultiThreadedDebugDLL</RuntimeLibrary>\n";
                break;
            }
            case BuildConfigurationType::Release:
            {
                res += "        <FunctionLevelLinking>true</FunctionLevelLinking>\n";
                res += "        <IntrinsicFunctions>true</IntrinsicFunctions>\n";
                res += "        <RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>\n";
                break;
            }
            case BuildConfigurationType::Retail:
            {
                res += "        <FunctionLevelLinking>true</FunctionLevelLinking>\n";
                res += "        <IntrinsicFunctions>true</IntrinsicFunctions>\n";
                res += "        <RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>\n";
                break;
            }
            default:
                break; // todo. error
            }

            res += "    </ClCompile>\n";
            res += "    <Link>\n";
            res += "      <SubSystem>Console</SubSystem>\n";

            switch (configuration.type)
            {
            case BuildConfigurationType::Debug:
            {
                res += "        <GenerateDebugInformation>true</GenerateDebugInformation>\n";
                res += "        <OptimizeReferences>false</OptimizeReferences>\n";
                res += "        <EnableCOMDATFolding>false</EnableCOMDATFolding>\n";
                break;
            }
            case BuildConfigurationType::Release:
            {
                res += "        <GenerateDebugInformation>false</GenerateDebugInformation>\n";
                res += "        <OptimizeReferences>true</OptimizeReferences>\n";
                res += "        <EnableCOMDATFolding>true</EnableCOMDATFolding>\n";
                break;
            }
            case BuildConfigurationType::Retail:
            {
                res += "        <GenerateDebugInformation>false</GenerateDebugInformation>\n";
                res += "        <OptimizeReferences>true</OptimizeReferences>\n";
                res += "        <EnableCOMDATFolding>true</EnableCOMDATFolding>\n";
                break;
            }
            default:
                break; // todo. error
            }

            res += "        <PreprocessorDefinitions>";

            switch (configuration.type)
            {
            case BuildConfigurationType::Debug:
            {
                res += "_DEBUG;";
                break;
            }
            case BuildConfigurationType::Release:
            {
                res += "NDEBUG;";
                break;
            }
            case BuildConfigurationType::Retail:
            {
                res += "NDEBUG;";
                break;
            }
            default:
                break; // todo. error
            }

            for (const std::string& preprocessorDefinition : pProject->preprocessorDefinitions)
            {
                res += preprocessorDefinition + ";";
            }

            res += "%(PreprocessorDefinitions)</PreprocessorDefinitions>\n";
            res += "    </Link>\n";
            res += "  </ItemDefinitionGroup>\n";
        }

        if (pProject->bUsePrecompiledHeaders)
        {
            res += "  <ItemGroup>\n";
            res += "    <ClInclude Include=\"..\\..\\..\\" + pProject->name + "\\" +
                pProject->precompiledHeaderName + ".hpp\"/>\n";
            res += "  </ItemGroup>\n";
            res += "  <ItemGroup>\n";
            res += "    <ClCompile Include=\"..\\..\\..\\" + pProject->name + "\\" +
                pProject->precompiledHeaderName + ".cpp\">\n";
        }

        for (const auto& configuration : pProject->configurations)
        {
            res += "      <PrecompiledHeader Condition=\"'$(Configuration)|$(Platform)'=='" +
                configuration.name + "|" + configuration.architecture + "'\">Create</PrecompiledHeader>\n";
        }

        res += "    </ClCompile>\n";
        res += "  </ItemGroup>\n";
        res += "  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\"/>\n";
        res += "  <ImportGroup Label=\"ExtensionTargets\">\n";
        res += "  </ImportGroup>\n";
        res += "</Project>";

        GenerateSourceDirectory(pProject);

        if (pProject->bUsePrecompiledHeaders)
        {
            GeneratePrecompiledHeader(pProject);
        }

        return std::move(res);
    }

    void VSProjectGenerator::GenerateSourceDirectory(Project* pProject)
    {
        if (!std::filesystem::is_directory(pProject->name))
        {
            std::filesystem::create_directory(pProject->name);
        }
    }

    void VSProjectGenerator::GeneratePrecompiledHeader(Project* pProject)
    {
        // todo. generate only if they don't exist

        // todo. LicenseType.hpp/.cpp (and load text from file) - and select in solution, and developer name
        static std::string licenseStr =
            "/*****************************************************************************************************************************\n"
            " * Copyright 2020 Gabriel Gheorghe. All rights reserved.\n"
            " * This code is licensed under the BSD 3-Clause \"New\" or \"Revised\" License\n"
            " * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE\n"
            " *****************************************************************************************************************************/\n";

        std::string headerPath = pProject->name + "\\" + pProject->precompiledHeaderName + ".hpp";
        std::string sourcePath = pProject->name + "\\" + pProject->precompiledHeaderName + ".cpp";

        if (!std::filesystem::exists(headerPath))
        {
            std::fstream fHeader;

            fHeader.open(headerPath.c_str(), std::ios::out);

            fHeader << licenseStr + "\n";
            fHeader << "#pragma once\n";

            fHeader.close();
        }

        if (!std::filesystem::exists(sourcePath))
        {
            std::fstream fSource;

            fSource.open(sourcePath.c_str(), std::ios::out);

            fSource << licenseStr + "\n\n";
            fSource << "#include <" + pProject->precompiledHeaderName + ".hpp>\n";

            fSource.close();
        }
    }
}