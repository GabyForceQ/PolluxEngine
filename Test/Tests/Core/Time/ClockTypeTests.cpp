/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Test/testpch.hpp"

#include "ClockTypeTests.hpp"
#include "Engine/Core/Time/ClockType.hpp"

using namespace Pollux::Core;

namespace Pollux::Test
{
    UnitTestResult ClockTypeConversion()
    {
        UnitTestResult res;
        static const char* pErrorMessage = "ClockType conversion FAILED";

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