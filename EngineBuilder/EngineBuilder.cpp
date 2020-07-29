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

    try
    {
        BuildAction buildAction = BuildAction::None;
        std::string projectPath = "Build\\Projects\\test\\";
        std::set<ProjectType> projectTypes;
        std::string targetName;
        ISolutionGenerator* pSolutionGenerator = nullptr;
        IProjectGenerator* pProjectGenerator = nullptr;
        PolluxEngineSolution* pSolution = nullptr;
        std::string solutionCode;
        std::vector<Project*> pProjects;

        struct ProjectsCode
        {
            std::string name;
            std::string path;
            std::string code;
        };

        std::vector<ProjectsCode> projectsCode;

        for (int i = 1; i < argc; i++)
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
            EngineProject* pEngineProject = new EngineProject();
            pEngineProject->ConfigureWin64();
            pProjects.push_back(pEngineProject);

            EditorProject* pEditorProject = new EditorProject();
            pEditorProject->ConfigureWin64();
            pProjects.push_back(pEditorProject);

            for (const auto projectType : projectTypes)
            {
                switch (projectType)
                {
                case ProjectType::VS2019:
                {
                    pSolutionGenerator = new VSSolutionGenerator();
                    pProjectGenerator = new VSProjectGenerator();

                    pSolution = new PolluxEngineSolution(pProjects);
                    pSolution->SetProjectType(projectType);
                    pSolution->ConfigureWin64();

                    projectsCode.push_back({ pEngineProject->GetName(), pEngineProject->GetPath(), pProjectGenerator->Generate(pEngineProject) });
                    projectsCode.push_back({ pEditorProject->GetName(), pEditorProject->GetPath(), pProjectGenerator->Generate(pEditorProject) });

                    solutionCode = pSolutionGenerator->Generate(pSolution);
                    
                    break;
                }
                }
            }

            break;
        }
        }

        std::fstream f((projectPath + "PolluxEngine.sln").c_str(), std::ios::out);
        f << solutionCode;
        f.close();

        for (const ProjectsCode& projectCode : projectsCode)
        {
            std::fstream f((projectPath + projectCode.path).c_str(), std::ios::out);
            f << projectCode.code;
            f.close();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}