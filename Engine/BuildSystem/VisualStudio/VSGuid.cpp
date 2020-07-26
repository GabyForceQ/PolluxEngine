/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "VSGuid.hpp"

namespace Pollux::BuildSystem
{
	VSGuid VSGuid::Create()
	{
        static std::random_device rd;
        static std::mt19937_64 mt(rd());

        const uint64_t randomTime = mt();

        const uint32_t timeLow = ((randomTime >> 24) & 0x000000FF) |
            ((randomTime >> 8) & 0x0000FF00) |
            ((randomTime << 8) & 0x00FF0000) |
            ((randomTime << 24) & 0xFF000000);

        const uint16_t timeMid = static_cast<uint16_t>(((randomTime >> 40) & 0x00FF) |
            ((randomTime >> 24) & 0xFF00));

        const uint16_t timeHiAndVersion = static_cast<uint16_t>(((0x04 << 12) & 0xF000) |
            ((randomTime >> 56) & 0x00FF) |
            ((randomTime >> 40) & 0x0F00));

        const uint16_t clockSequence = static_cast<uint16_t>(mt() & 0x3FFF);
        const uint8_t clockSeqHiAndReserved = static_cast<uint8_t>(0x80 | ((clockSequence >> 8) & 0x3F));
        const uint8_t clockSeqLow = static_cast<uint8_t>(clockSequence & 0xFF);
        const uint64_t random = mt();

        VSGuid res
        {
            timeLow,
            timeMid,
            timeHiAndVersion,
            clockSeqHiAndReserved,
            clockSeqLow,
            {
                static_cast<uint8_t>(random >> 48),
                static_cast<uint8_t>(random >> 40),
                static_cast<uint8_t>(random >> 32),
                static_cast<uint8_t>(random >> 24),
                static_cast<uint8_t>(random >> 16),
                static_cast<uint8_t>(random >> 0)
            }
        };

        return std::move(res);
	}

    std::string VSGuid::ToString() const noexcept
    {
        constexpr char digits[] = "0123456789abcdef";

        std::string res
        {
            digits[(timeLow >> 28) & 0x0F],
            digits[(timeLow >> 24) & 0x0F],
            digits[(timeLow >> 20) & 0x0F],
            digits[(timeLow >> 16) & 0x0F],
            digits[(timeLow >> 12) & 0x0F],
            digits[(timeLow >> 8) & 0x0F],
            digits[(timeLow >> 4) & 0x0F],
            digits[(timeLow >> 0) & 0x0F],
            '-',
            digits[(timeMid >> 12) & 0x0F],
            digits[(timeMid >> 8) & 0x0F],
            digits[(timeMid >> 4) & 0x0F],
            digits[(timeMid >> 0) & 0x0F],
            '-',
            digits[(timeHiAndVersion >> 12) & 0x0F],
            digits[(timeHiAndVersion >> 8) & 0x0F],
            digits[(timeHiAndVersion >> 4) & 0x0F],
            digits[(timeHiAndVersion >> 0) & 0x0F],
            '-',
            digits[(clockSeqHiAndReserved >> 4) & 0x0F],
            digits[(clockSeqHiAndReserved >> 0) & 0x0F],
            digits[(clockSeqLow >> 4) & 0x0F],
            digits[(clockSeqLow >> 0) & 0x0F],
            '-',
            digits[(node[0] >> 4) & 0x0F],
            digits[(node[0] >> 0) & 0x0F],
            digits[(node[1] >> 4) & 0x0F],
            digits[(node[1] >> 0) & 0x0F],
            digits[(node[2] >> 4) & 0x0F],
            digits[(node[2] >> 0) & 0x0F],
            digits[(node[3] >> 4) & 0x0F],
            digits[(node[3] >> 0) & 0x0F],
            digits[(node[4] >> 4) & 0x0F],
            digits[(node[4] >> 0) & 0x0F],
            digits[(node[5] >> 4) & 0x0F],
            digits[(node[5] >> 0) & 0x0F]
        };

        return std::move(res);
    }
}