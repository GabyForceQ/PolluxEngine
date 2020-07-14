/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ClockType.hpp"

namespace Pollux::Core
{
    const char* g_pClockType_Win32Clock = "ClockType::Win32Clock";
    const char* g_pClockType_ResolutionClock = "ClockType::ResolutionClock";
    const char* g_pClockType_SteadyClock = "ClockType::SteadyClock";

    const std::map<const char*, ClockType> g_ClockTypeMap
    {
        { g_pClockType_Win32Clock, ClockType::Win32Clock },
        { g_pClockType_ResolutionClock, ClockType::ResolutionClock },
        { g_pClockType_SteadyClock, ClockType::SteadyClock }
    };

    ClockType ClockTypeToEnum(const char* clockType)
    {
        if (g_ClockTypeMap.contains(clockType))
        {
            return g_ClockTypeMap.at(clockType);
        }

        throw std::runtime_error("Clock Type string is not valid");
    }

    const char* ToString(const ClockType& clockType) noexcept
    {
        switch (clockType)
        {
            case ClockType::Win32Clock:
            {
                return g_pClockType_Win32Clock;
            }
            case ClockType::ResolutionClock:
            {
                return g_pClockType_ResolutionClock;
            }
            case ClockType::SteadyClock:
            {
                return g_pClockType_SteadyClock;
            }
            default:
            {
                // todo. Log a warning message
            }
        }

        return g_pEmptyString;
    }
}