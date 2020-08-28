/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Compiler.hpp"
#include "CompilerUnit.hpp"
#include "../Symbol/SymbolTable.hpp"

namespace Pollux::Lang
{
    Compiler::Compiler(std::string srcFolderName) noexcept
        :
        srcFolderName{ std::move(srcFolderName) }
    {
    }

    void Compiler::Initialize(const std::deque<std::string> units)
    {
        bLocal = true;

        for (size_t i = 0_sz; i < units.size(); i++)
        {
            compilerUnitMap.insert(make_pair
            (
                "Unit" + std::to_string(i),
                new CompilerUnit(this))
            );

            //compilerUnitMap["Unit" + std::to_string(i)]->stringMap.insert(std::make_pair
            //(
            //    "Unit" + std::to_string(i),
            //    units[i]
            //));
        }
    }

    void Compiler::Initialize()
    {
        std::filesystem::path path(srcFolderName);

        if (!std::filesystem::exists(path) && !std::filesystem::is_directory(path))
        {
            throw std::runtime_error("Invalid path!");
        }

        ParseSrcFolders(srcFolderName, 0);
    }

    void Compiler::BuildPrecompiledHeader()
    {
        std::fstream f;
        f.open("..\\..\\..\\lang_gen\\LOCALPCH.HPP", std::ios::out);
        f << ""; // todo.
        f.close();

        f.open("..\\..\\..\\lang_gen\\LOCALPCH.CPP", std::ios::out);
        f << "#include\"LOCALPCH.HPP\"\n";
        f.close();
    }

    void Compiler::BuildMain()
    {
        std::string incName = "";
        std::string name = "";

        for (const auto& unit : compilerUnitMap)
        {
            //if (unit.second->is_main)
            //{
            //    incName = "UNIT_" + unit.second->upper_name + ".HPP";
            //    name = unit.second->full_name;
            //}
        }

        std::fstream f;
        f.open("..\\..\\..\\lang_gen\\UNIT_MAIN.CPP", std::ios::out);

        f << "#include\"LOCALPCH.HPP\"\n#include<pollux/EnginePackage.hpp>\n#include\"PROTOTYPES.HPP\"\n"
            << "#include\"" << incName << "\"\nvoid __init(){\n";

        for (const auto& pUnit : compilerUnitMap)
        {
            f << pUnit.second->full_name << "=std::make_unique<"
                << pUnit.second->full_upper_name << ">();\n";
        }

        f << "}\nint32_t __ctor(){\nreturn " << name << "->"
            << "__ctor();\n}\n" << "POLLUX_APPLICATION()\n";

        f.close();
    }

    void Compiler::GetSymbolTable()
    {
    }

    void Compiler::Compile()
    {
        for (const auto& unit : compilerUnitMap)
        {
            unit.second->tokenize();
            
            if (!bLocal)
            {
                // TODO. impl for parse_symbol_table
                unit.second->parse_symbol_table();
            }
            
            unit.second->parse();
        }
    }

    void Compiler::Build()
    {
        BuildPrecompiledHeader();
        BuildMain();

        for (const auto& unit : compilerUnitMap)
        {
            unit.second->build_header();
            unit.second->build_source();
        }
    }

    void Compiler::Run()
    {
    }

    const std::deque<std::string> Compiler::GetVersionIdentifiers() const
    {
        std::deque<std::string> res;
#ifdef POLLUX_SYSTEM_WINDOWS
        res.push_back("OS_Windows");
#endif
#ifdef POLLUX_TARGET_DEBUG
        res.push_back("CFG_Debug");
#endif
        return res;
    }

    bool Compiler::IsLocal() const noexcept
    {
        return bLocal;
    }

    void Compiler::ParseSrcFolders(const std::filesystem::path& pathToShow, const int32_t level)
    {
        uint32_t files = 0u;

        if (std::filesystem::exists(pathToShow) && std::filesystem::is_directory(pathToShow))
        {
            std::unordered_map<std::string, CompilerUnitFile> filePathMap = {};
            std::string name_ = "";
            auto lead = std::string(level * 3, ' ');
            
            for (const auto& entry : std::filesystem::directory_iterator(pathToShow))
            {
                auto filename = entry.path().filename();
                auto path = entry.path().relative_path();

                if (std::filesystem::is_directory(entry.status()))
                {
                    ParseSrcFolders(entry, level + 1);
                }
                else if (std::filesystem::is_regular_file(entry.status()))
                {
                    // Store file's relative path.
                    std::string relPath_ = pathToShow.root_path().generic_string()
                        + path.relative_path().generic_string();

                    // Store file's name.
                    name_ = relPath_;
                    size_t startPos = 0, endPos = 0;

                    for (size_t i = name_.size() - 1; i > 0; i--)
                    {
                        if (name_[i] == '.')
                        {
                            endPos = i;
                        }
                        else if (name_[i] == '/'
                            && name_[i - 1] == 'c'
                            && name_[i - 2] == 'r'
                            && name_[i - 3] == 's'
                            && name_[i - 4] == '/')
                        {
                            startPos = i + 1;
                            break;
                        }
                    }

                    name_ = name_.substr(startPos, endPos - startPos);

                    // Store file's absolute path.
                    std::string absPath_ = "src/" + name_ + ".px";

                    // Store dotted name.
                    std::string dottedName_ = name_;
                    for (auto& c : dottedName_)
                    {
                        if (c == '/')
                        {
                            c = '.';
                        }
                    }

                    auto cuf = CompilerUnitFile(relPath_, absPath_, dottedName_);

                    // TODO. Insert absolute path
                    filePathMap.insert(std::make_pair(name_, cuf));

                    files++;
                }
                else
                {
                    throw std::runtime_error("Unknown!");
                }
            }

            if (files > 0)
            {
                size_t endPos = 0;

                // Store unit's symbol name.
                std::string unitSymbolName_ = name_;
                for (auto& c : unitSymbolName_)
                {
                    if (c == '/')
                    {
                        c = '.';
                    }
                }

                for (size_t i = unitSymbolName_.size() - 1; i > 0; i--)
                {
                    if (unitSymbolName_[i] == '.')
                    {
                        endPos = i;
                        break;
                    }
                }

                unitSymbolName_ = unitSymbolName_.substr(0, endPos);

                // Store unit's name.
                std::string unitName_ = unitSymbolName_;
                for (auto& c : unitName_)
                {
                    if (c == '.')
                    {
                        c = '_';
                    }
                }

                // Store unit's uppercase name.
                std::string unitUpName_ = unitName_;

                for (auto& c : unitUpName_)
                {
                    c = toupper(c);
                }

                // Store unit's full name.
                std::string unitFullName_ = "__unit_" + unitName_ + "__";

                // Store unit's full upperscase name.
                std::string unitFullUpName_ = "__UNIT_" + unitUpName_ + "__";

                std::string dirPath = unitName_;

                compilerUnitMap.insert(std::make_pair(dirPath, new CompilerUnit(this)));

                compilerUnitMap[dirPath]->name = unitName_;
                compilerUnitMap[dirPath]->upper_name = unitUpName_;
                compilerUnitMap[dirPath]->full_name = unitFullName_;
                compilerUnitMap[dirPath]->full_upper_name = unitFullUpName_;
                compilerUnitMap[dirPath]->symbol_name = unitSymbolName_;
                compilerUnitMap[dirPath]->file_map.insert(filePathMap.begin(), filePathMap.end());
                compilerUnitMap[dirPath]->symbol_table = new SymbolTable(/*unitSymbolName_*/);
            }
        }
    }
}