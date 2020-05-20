/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"
#include "ClockTypeTests.hpp"
#include "../ClockType.hpp"

#ifdef POLLUX_TARGET_UNITTEST

namespace Pollux::Core::Test
{
    UnitTestResult ClockTypeTest_Conversion()
    {
        UnitTestResult res;
        bool ok = true;
        static const char* pErrorMessage = "ClockTypeTest_Conversion() FAILED";

        for (const auto& e : g_ClockTypeMap)
        {
            if (strcmp(ToString(ClockTypeToEnum(e.first)), e.first) != 0)
            {
                res.succeeded = false;
                res.message = pErrorMessage;
                
                break;
            }
        }

        return std::move(res);
    }
}

#endif