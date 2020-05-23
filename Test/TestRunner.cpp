/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Test/testpch.hpp"

#include "TestRunner.hpp"
#include "Tests/Core/ConcurrencyTests.hpp"
#include "Tests/Core/Time/ClockTypeTests.hpp"

namespace Pollux::Test
{
    void RunAllTests()
    {
        static const char* pSuccessMessage = "All tests were passed successfully!\n\n";
        static const char* pFilureMessage = " tests failed!\n\n";
        uint32_t errors = 0;

        // Core.Concurrency
        {
            RUN_TEST(CreateDestroyWorkerThread);
            RUN_TEST(SetNameToWorkerThread);
        }

        // Core.Time
        {
            RUN_TEST(ClockTypeConversion);
        }

        if (errors == 0)
        {
            std::cout << pSuccessMessage;
        }
        else
        {
            std::cout << errors << pFilureMessage;
        }
    }
}

int main(int argc, char* argv[])
{
    Pollux::Test::RunAllTests();
    return 0;
}