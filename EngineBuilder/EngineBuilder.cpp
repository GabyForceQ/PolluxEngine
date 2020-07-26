/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "EngineBuilder/enginebuilderpch.hpp"

using namespace Pollux::BuildSystem;

int main(int argc, char* argv[])
{
    try
    {
        BuildAction buildAction = BuildAction::None;
        std::string projectPath = "Build\\Projects\\Win64_VS2019\\";
        std::set<ProjectType> projectTypes;
        std::string targetName;
        ISolutionGenerator* pSolutionGenerator = nullptr;
        Solution* pSolution = nullptr;
        std::string solutionCode;

        for (int i = 1; i < argc; ++i)
        {
            if (std::string(argv[i]) == "--help")
            {
                std::cout << "Usage:\n" << argv[0] << "\n[--help]:\n"
                    "  [--generate-project <project-file>]\n"
                    "  [--project <all|vs2019>]\n"
                    "  [--target <target-name>]\n";

                return 0;
            }
            else if (std::string(argv[i]) == "--generate-project")
            {
                buildAction = BuildAction::GenerateProject;

                if (++i < argc)
                {
                    projectPath = std::string(argv[i]);
                }
            }
            else if (std::string(argv[i]) == "--project")
            {
                if (++i >= argc)
                {
                    throw std::runtime_error("Invalid command.");
                }

                if (std::string(argv[i]) == "all")
                {
                    projectTypes.insert(ProjectType::VS2019);
                }
                else if (std::string(argv[i]) == "vs2019")
                {
                    projectTypes.insert(ProjectType::VS2019);
                }
                else
                {
                    throw std::runtime_error("Invalid project.");
                }
            }
            else if (std::string(argv[i]) == "--target")
            {
                if (++i >= argc)
                {
                    throw std::runtime_error("Invalid command.");
                }

                targetName = argv[i];
            }
        }

        switch (buildAction)
        {
        case BuildAction::None:
        {
            throw std::runtime_error("No action selected.");
        }
        case BuildAction::GenerateProject:
        {
            Project* project = new Project();
            project->path = projectPath;

            for (const auto projectType : projectTypes)
            {
                switch (projectType)
                {
                case ProjectType::VS2019:
                {
                    pSolutionGenerator = new VSSolutionGenerator();
                    pSolution = new VSSolution();

                    solutionCode = pSolutionGenerator->Generate(pSolution);
                    
                    break;
                }
                default:
                {
                    // todo. log error
                    break;
                }
                }
            }

            break;
        }
        default:
        {
            // todo. log error
            break;
        }
        }

        std::fstream f((projectPath + "PolluxEngine").c_str(), std::ios::out);
        f << solutionCode;
        f.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}