/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Core
{
    /**************************************************************************************************************************
     * \enum Clock Type
     *************************************************************************************************************************/
    enum class ClockType
    {
        /**********************************************************************************************************************
         * \brief Windows 32 High Resolution Clock
         *********************************************************************************************************************/
        Win32Clock,
        
        /**********************************************************************************************************************
         * \brief High Resolution Clock
         *
         * This is the clock with the smallest tick period provided by the STL implementation
         *********************************************************************************************************************/
        ResolutionClock,
        
        /**********************************************************************************************************************
         * \brief Monotonic clock
         *
         * The time points of this clock can't decrease as physical time moves forward and the time between ticks of this
         * clock is constant. This clock is not related to wall clock time, for example, it can be time since last reboot
         * and is most suitable for measuring intervals
         *********************************************************************************************************************/
        SteadyClock
    };

    /**************************************************************************************************************************
     * \brief Clock Type Win32 Clock string
     * \see ClockType::Win32Clock
     *************************************************************************************************************************/
    extern const char* g_pClockType_Win32Clock;

    /**************************************************************************************************************************
     * \brief Clock Type Resolution Clock string
     * \see ClockType::ResolutionClock
     *************************************************************************************************************************/
    extern const char* g_pClockType_ResolutionClock;
    
    /**************************************************************************************************************************
     * \brief Clock Type Steady Clock string
     * \see ClockType::SteadyClock
     *************************************************************************************************************************/
    extern const char* g_pClockType_SteadyClock;

    /**************************************************************************************************************************
     * \brief Clock Type Map
     * \see ClockType
     *
     * Access an enum field by its string
     *************************************************************************************************************************/
    extern const std::map<const char*, ClockType> g_ClockTypeMap;

    /**************************************************************************************************************************
     * \return Clock Type as enum
     * \param Clock Type string
     * \exception Runtime error: Clock Type string is not valid
     * \see ClockType
     *
     * The string should be composed by the enum class name followed by :: followed by the enum field name
     * (e.g. "EnumClassName::EnumFieldName")
     *************************************************************************************************************************/
    ClockType ClockTypeToEnum(const char* clockType);

    /**************************************************************************************************************************
     * \return Clock Type as string
     * \param Clock Type enum
     * \see ClockType
     *
     * The returned string will be composed by the enum class name followed by :: followed by the enum field name
     * (e.g. "EnumClassName::EnumFieldName")
     * If the field conversion is not implemented, an warning message will be shown and an empty string will be returned
     *************************************************************************************************************************/
    const char* ToString(const ClockType& clockType) noexcept;
}