/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux
{
    /**************************************************************************************************************************
     * \class UTF8 Parse Error
     *************************************************************************************************************************/
    class UTF8ParseError final : public std::logic_error
    {
    public:
        explicit UTF8ParseError(const char* message);
    };
}