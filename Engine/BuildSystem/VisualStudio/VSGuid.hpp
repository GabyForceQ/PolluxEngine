/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::BuildSystem
{
	struct VSGuid final
	{
        uint32_t timeLow;
        
        uint16_t timeMid;
        
        uint16_t timeHiAndVersion;
        
        uint8_t clockSeqHiAndReserved;
        
        uint8_t clockSeqLow;
        
        uint8_t node[6];

        static VSGuid Create();

        std::string ToString() const noexcept;
	};
}