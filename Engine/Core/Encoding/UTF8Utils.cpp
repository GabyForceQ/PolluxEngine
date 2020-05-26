/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "UTF8Utils.hpp"

namespace Pollux
{
	std::string UTF8Utils::FromUTF32(const char32_t& c)
	{
        std::string res;

        if (c <= 0x7F)
        {
            res.push_back(static_cast<char>(c));
        }
        else if (c <= 0x7FF)
        {
            res.push_back(static_cast<char>(0xC0 | ((c >> 6) & 0x1F)));
            res.push_back(static_cast<char>(0x80 | (c & 0x3F)));
        }
        else if (c <= 0xFFFF)
        {
            res.push_back(static_cast<char>(0xE0 | ((c >> 12) & 0x0F)));
            res.push_back(static_cast<char>(0x80 | ((c >> 6) & 0x3F)));
            res.push_back(static_cast<char>(0x80 | (c & 0x3F)));
        }
        else
        {
            res.push_back(static_cast<char>(0xF0 | ((c >> 18) & 0x07)));
            res.push_back(static_cast<char>(0x80 | ((c >> 12) & 0x3F)));
            res.push_back(static_cast<char>(0x80 | ((c >> 6) & 0x3F)));
            res.push_back(static_cast<char>(0x80 | (c & 0x3F)));
        }

        return res;
	}
}