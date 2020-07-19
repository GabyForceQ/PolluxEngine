/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "FileStatus.hpp"

namespace Pollux::Core
{
    const char* g_pFileStatus_Created = "FileStatus::Created";
    const char* g_pFileStatus_Modified = "FileStatus::Modified";
    const char* g_pFileStatus_Erased = "FileStatus::Erased";

    const std::map<const char*, FileStatus> g_FileStatusMap
    {
        { g_pFileStatus_Created, FileStatus::Created },
        { g_pFileStatus_Modified, FileStatus::Modified },
        { g_pFileStatus_Erased, FileStatus::Erased }
    };

    FileStatus FileStatusToEnum(const char* fileStatus)
    {
        if (g_FileStatusMap.contains(fileStatus))
        {
            return g_FileStatusMap.at(fileStatus);
        }

        throw std::runtime_error("Error (Core.Storage): File Status string is not valid.");
    }

    const char* ToString(const FileStatus& fileStatus) noexcept
    {
        switch (fileStatus)
        {
            case FileStatus::Created:
            {
                return g_pFileStatus_Created;
            }
            case FileStatus::Modified:
            {
                return g_pFileStatus_Modified;
            }
            case FileStatus::Erased:
            {
                return g_pFileStatus_Erased;
            }
            default:
            {
                // todo. Log a warning message
            }
        }

        return g_pEmptyString;
    }
}