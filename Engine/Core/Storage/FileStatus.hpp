/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Core
{
    /*************************************************************************************************************************
     * \enum File Status
     *************************************************************************************************************************/
    enum class FileStatus
    {
        /*********************************************************************************************************************
         * File is just created
         *********************************************************************************************************************/
        Created,

        /*********************************************************************************************************************
         * File is just modified
         *********************************************************************************************************************/
        Modified,

        /*********************************************************************************************************************
         * File is just erased
         *********************************************************************************************************************/
        Erased
    };

    /**************************************************************************************************************************
     * File Status Created string
     *
     * \see FileStatus::Created
     *************************************************************************************************************************/
    extern const char* g_pFileStatus_Created;

    /**************************************************************************************************************************
     * File Status Modified string
     *
     * \see FileStatus::Modified
     *************************************************************************************************************************/
    extern const char* g_pFileStatus_Modified;

    /**************************************************************************************************************************
     * File Status Erased string
     *
     * \see FileStatus::Erased
     *************************************************************************************************************************/
    extern const char* g_pFileStatus_Erased;

    /**************************************************************************************************************************
     * File Status Map
     *
     * \brief Access an enum field by its string
     * \see FileStatus
     *************************************************************************************************************************/
    extern const std::map<const char*, FileStatus> g_FileStatusMap;

    /**************************************************************************************************************************
     * \return File Status as enum
     * \param fileStatus string
     * \exception Runtime error: File Status string is not valid
     * \see FileStatus
     * \note The string should be composed by the enum class name followed by :: followed by the enum field name
     * (e.g. "EnumClassName::EnumFieldName")
     *************************************************************************************************************************/
    FileStatus FileStatusToEnum(const char* fileStatus);

    /**************************************************************************************************************************
     * \return File Status as string
     * \param fileStatus enum
     * \see FileStatus
     * \note The returned string will be composed by the enum class name followed by :: followed by the enum field name
     * (e.g. "EnumClassName::EnumFieldName")
     * If the field conversion is not implemented, an warning message will be shown and an empty string will be returned
     *************************************************************************************************************************/
    const char* ToString(const FileStatus& fileStatus) noexcept;
}