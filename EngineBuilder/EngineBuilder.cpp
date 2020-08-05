/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "EngineBuilder/enginebuilderpch.hpp"

#include "EngineProject.hpp"
#include "EditorProject.hpp"

#include "PolluxEngineSolution.hpp"

using namespace Pollux::BuildSystem;
using namespace Pollux::EngineBuilder;

int main(int argc, char* argv[])
{
    srand(static_cast<uint32_t>(time(0)));

    BuildSystem* pBuildSystem = new BuildSystem();
    PolluxEngineSolution* pSolution = new PolluxEngineSolution("Build\\Projects\\Win64_VS2019\\");

    try
    {
        BuildAction buildAction = BuildAction::None;
        ISolutionGenerator* pSolutionGenerator = nullptr;
        IProjectGenerator* pProjectGenerator = nullptr;
        IProjectFiltersGenerator* pProjectFiltersGenerator = nullptr;
        std::string solutionCode;
        std::vector<Project*> pProjects;

        struct ProjectsCode
        {
            std::string name;
            std::string path;
            std::string code;
            std::string filtersPath;
            std::string filtersCode;
        };

        std::vector<ProjectsCode> projectsCode;

        for (size_t i = 1_sz; i < argc; i++)
        {
            if (std::string(argv[i]) == "--help")
            {
                std::cout << "Usage:\n" << argv[0] << "\n[--help]:\n"
                    "  [--generate-solution <makefile|vs2019|all>]\n"
                    "  [--platform <windows|linux|android|all>]\n"
                    "  [--optimization <basic|noretail>]\n"
                    "  [--type <engine|compiler|make>]\n";

                return 0;
            }
            else if (std::string(argv[i]) == "--generate-solution")
            {
                if (++i >= argc)
                {
                    throw std::runtime_error("Invalid command.");
                }

                if (std::string(argv[i]) == "makefile")
                {
                    pBuildSystem->target.developmentEnvironment = DevelopmentEnvironment::Makefile;
                }
                else if (std::string(argv[i]) == "vs2019")
                {
                    pBuildSystem->target.developmentEnvironment = DevelopmentEnvironment::VS2019;
                }
                else if (std::string(argv[i]) == "all")
                {
                    pBuildSystem->target.developmentEnvironment =
                        DevelopmentEnvironment::Makefile |
                        DevelopmentEnvironment::VS2019;
                }
                else
                {
                    throw std::runtime_error("Invalid development environment.");
                }

                buildAction = BuildAction::GenerateSolution;
            }
            else if (std::string(argv[i]) == "--platform")
            {
                if (++i >= argc)
                {
                    throw std::runtime_error("Invalid command.");
                }

                if (std::string(argv[i]) == "windows")
                {
                    pBuildSystem->target.platform = BuildPlatform::Windows;
                }
                else if (std::string(argv[i]) == "linux")
                {
                    pBuildSystem->target.platform = BuildPlatform::Linux;
                }
                else if (std::string(argv[i]) == "android")
                {
                    pBuildSystem->target.platform = BuildPlatform::Android;
                }
                else if (std::string(argv[i]) == "all")
                {
                    pBuildSystem->target.platform =
                        BuildPlatform::Windows |
                        BuildPlatform::Linux |
                        BuildPlatform::Android;
                }
                else
                {
                    throw std::runtime_error("Invalid platform.");
                }
            }
            else if (std::string(argv[i]) == "--optimization")
            {
                if (++i >= argc)
                {
                    throw std::runtime_error("Invalid command.");
                }

                if (std::string(argv[i]) == "basic")
                {
                    pBuildSystem->target.optimization =
                        BuildOptimization::Debug |
                        BuildOptimization::Release |
                        BuildOptimization::Retail;

                    pBuildSystem->configurationMap[BuildOptimization::Debug] =
                        new BuildConfiguration(BuildOptimization::Debug);

                    pBuildSystem->configurationMap[BuildOptimization::Release] =
                        new BuildConfiguration(BuildOptimization::Release);

                    pBuildSystem->configurationMap[BuildOptimization::Retail] =
                        new BuildConfiguration(BuildOptimization::Retail);
                }
                else if (std::string(argv[i]) == "noretail")
                {
                    pBuildSystem->target.optimization =
                        BuildOptimization::Debug |
                        BuildOptimization::Release;

                    pBuildSystem->configurationMap[BuildOptimization::Debug] =
                        new BuildConfiguration(BuildOptimization::Debug);

                    pBuildSystem->configurationMap[BuildOptimization::Release] =
                        new BuildConfiguration(BuildOptimization::Release);
                }
                else
                {
                    throw std::runtime_error("Invalid optimization.");
                }

                pBuildSystem->globalConfiguration = new BuildConfiguration(BuildOptimization::None);
            }
            else if (std::string(argv[i]) == "--type")
            {
                if (++i >= argc)
                {
                    throw std::runtime_error("Invalid command.");
                }

                if (std::string(argv[i]) == "engine")
                {
                    pBuildSystem->globalConfiguration->preprocessorDefinitions.push_back("POLLUX_ENGINE");
                }
                else if (std::string() == "compiler")
                {
                    pBuildSystem->globalConfiguration->preprocessorDefinitions.push_back("POLLUX_COMPILER");
                }
                else if (std::string(argv[i]) == "make")
                {
                    pBuildSystem->globalConfiguration->preprocessorDefinitions.push_back("POLLUX_MAKE");
                }
                else
                {
                    throw std::runtime_error("Invalid build type.");
                }
            }
        }

        switch (buildAction)
        {
        case BuildAction::None:
        {
            throw std::runtime_error("No action selected.");
        }
        case BuildAction::GenerateSolution:
        {
            if (+pBuildSystem->target.developmentEnvironment & +DevelopmentEnvironment::VS2019)
            {
                pSolutionGenerator = new VSSolutionGenerator();
                pProjectGenerator = new VSProjectGenerator();
                pProjectFiltersGenerator = new VSProjectFiltersGenerator();

                for (Project* pProject : pSolution->pProjects)
                {
                    pProject->pVSProject = new VSProject();
                    pProject->pProjectFilters->pVSProjectFilters = new VSProjectFilters();
                    pProject->Initialize(pBuildSystem);
                }
            }

            pSolution->Implement(pBuildSystem, pProjectGenerator, pProjectFiltersGenerator);

            if (+pBuildSystem->target.platform & +BuildPlatform::Windows)
            {
                for (Project* pProject : pSolution->pProjects)
                {
                    projectsCode.push_back({ pProject->GetName(), pProject->GetPath(), pProject->GetGeneratedCode(),
                        pProject->pProjectFilters->GetPath(), pProject->pProjectFilters->GetGeneratedCode() });
                }

                solutionCode = pSolutionGenerator->Generate(pSolution);
            }

            if (!std::filesystem::is_directory("Build"))
            {
                std::filesystem::create_directory("Build");
            }

            for (const std::string& folder : { "Output", "Projects", "Temp" })
            {
                std::string folderPath = "Build\\" + folder;

                if (!std::filesystem::is_directory(folderPath))
                {
                    std::filesystem::create_directory(folderPath);
                }
            }

            for (const std::string& folder : { "Win64_VS2019_Debug" })
            {
                std::string folderPath = "Build\\Output\\" + folder;

                if (!std::filesystem::is_directory(folderPath))
                {
                    std::filesystem::create_directory(folderPath);
                }
            }

            for (const std::string& folder : { "Win64_VS2019" })
            {
                std::string folderPath = "Build\\Projects\\" + folder;

                if (!std::filesystem::is_directory(folderPath))
                {
                    std::filesystem::create_directory(folderPath);
                }
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019\\Editor"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019\\Editor");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019\\Editor\\Debug"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019\\Editor\\Debug");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019\\Editor\\Release"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019\\Editor\\Release");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019\\Editor\\Retail"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019\\Editor\\Retail");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019\\Engine"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019\\Engine");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019\\Engine\\Debug"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019\\Engine\\Debug");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019\\Engine\\Release"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019\\Engine\\Release");
            }

            if (!std::filesystem::is_directory("Build\\Temp\\Obj\\Win64_VS2019\\Engine\\Retail"))
            {
                std::filesystem::create_directory("Build\\Temp\\Obj\\Win64_VS2019\\Engine\\Retail");
            }

            std::fstream f("Build\\Projects\\Win64_VS2019\\PolluxEngine.sln", std::ios::out);
            f << solutionCode;
            f.close();

            for (const ProjectsCode& projectCode : projectsCode)
            {
                std::fstream f(("Build\\Projects\\Win64_VS2019\\" + projectCode.path).c_str(), std::ios::out);
                f << projectCode.code;
                f.close();

                std::fstream g(("Build\\Projects\\Win64_VS2019\\" + projectCode.filtersPath).c_str(), std::ios::out);
                g << projectCode.filtersCode;
                g.close();
            }

            break;
        }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    SAFE_DELETE(pBuildSystem);

    //..

    return 0;
}