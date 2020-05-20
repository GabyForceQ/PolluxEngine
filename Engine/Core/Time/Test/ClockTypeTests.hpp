/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#ifdef POLLUX_TARGET_UNITTEST

namespace Pollux::Core::Test
{
    /**************************************************************************************************************************
     * \brief Check if an enum of type ClockType is convertible to string and vice versa.
     * \return Test Result
     *************************************************************************************************************************/
    UnitTestResult ClockTypeTest_Conversion();
}

#endif