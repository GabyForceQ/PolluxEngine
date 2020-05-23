/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "ThisThread.hpp"

namespace Pollux::Core
{
    void ThisThread::SetName(const char* name)
    {
        constexpr DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push, 8)

        struct THREADNAME_INFO
        {
            DWORD dwType;
            LPCSTR szName;
            DWORD dwThreadID;
            DWORD dwFlags;
        };

#pragma pack(pop)

        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = name;
        info.dwThreadID = static_cast<DWORD>(-1);
        info.dwFlags = 0;

        const DWORD numberOfArguments = sizeof(info) / sizeof(ULONG_PTR);
        ULONG_PTR arguments[numberOfArguments];
        memcpy(arguments, &info, sizeof(info));

        __try
        {
            RaiseException(MS_VC_EXCEPTION, 0, numberOfArguments, arguments);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }

    void ThisThread::SleepForMilliseconds(const uint32_t& milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void ThisThread::SleepForSeconds(const uint32_t& seconds)
    {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }
}