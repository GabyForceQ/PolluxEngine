/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "UTF8ParseError.hpp"
#include "../OOP/OOPUtils.hpp"

namespace Pollux
{
    /**************************************************************************************************************************
     * \class UTF8 Utilities - static
     *************************************************************************************************************************/
	class UTF8Utils final : public NonCopyableNorMovable<UTF8Utils>
	{
	public:
		template <typename ITERATOR>
		static std::u32string ToUTF32(ITERATOR begin, ITERATOR end)
		{
            std::u32string res;

            for (auto it = begin; it != end; ++it)
            {
                char32_t cp = *it & 0xFF;

                if (cp <= 0x7F)
                {
                }
                else if ((cp >> 5) == 0x6)
                {
                    if (++it == end)
                    {
                        throw UTF8ParseError("Invalid UTF-8 string.");
                    }

                    cp = ((cp << 6) & 0x7FF) + (*it & 0x3F);
                }
                else if ((cp >> 4) == 0xE)
                {
                    if (++it == end)
                    {
                        throw UTF8ParseError("Invalid UTF-8 string.");
                    }
                    
                    cp = ((cp << 12) & 0xFFFF) + (((*it & 0xFF) << 6) & 0x0FFF);
                    
                    if (++it == end)
                    {
                        throw UTF8ParseError("Invalid UTF-8 string.");
                    }
                    
                    cp += *it & 0x3F;
                }
                else if ((cp >> 3) == 0x1E)
                {
                    if (++it == end)
                    {
                        throw UTF8ParseError("Invalid UTF-8 string.");
                    }

                    cp = ((cp << 18) & 0x1FFFFF) + (((*it & 0xFF) << 12) & 0x3FFFF);
                    
                    if (++it == end)
                    {
                        throw UTF8ParseError("Invalid UTF-8 string.");
                    }
                    
                    cp += ((*it & 0xFF) << 6) & 0x0FFF;
                    
                    if (++it == end)
                    {
                        throw UTF8ParseError("Invalid UTF-8 string.");
                    }
                    
                    cp += *it & 0x3F;
                }

                res.push_back(cp);
            }

            return res;
		}

		template <typename T>
        static std::u32string ToUTF32(const T& text)
        {
            return ToUTF32(std::begin(text), std::end(text));
        }

        template <typename ITERATOR>
        static std::string FromUTF32(ITERATOR begin, ITERATOR end)
        {
            std::string res;

            for (auto it = begin; it != end; ++it)
            {
                if (*it <= 0x7F)
                {
                    res.push_back(static_cast<char>(*it));
                }
                else if (*it <= 0x7FF)
                {
                    res.push_back(static_cast<char>(0xC0 | ((*it >> 6) & 0x1F)));
                    res.push_back(static_cast<char>(0x80 | (*it & 0x3F)));
                }
                else if (*it <= 0xFFFF)
                {
                    res.push_back(static_cast<char>(0xE0 | ((*it >> 12) & 0x0F)));
                    res.push_back(static_cast<char>(0x80 | ((*it >> 6) & 0x3F)));
                    res.push_back(static_cast<char>(0x80 | (*it & 0x3F)));
                }
                else
                {
                    res.push_back(static_cast<char>(0xF0 | ((*it >> 18) & 0x07)));
                    res.push_back(static_cast<char>(0x80 | ((*it >> 12) & 0x3F)));
                    res.push_back(static_cast<char>(0x80 | ((*it >> 6) & 0x3F)));
                    res.push_back(static_cast<char>(0x80 | (*it & 0x3F)));
                }
            }

            return res;
        }

        template <typename T>
        static std::string FromUTF32(const T& text)
        {
            return FromUTF32(std::begin(text), std::end(text));
        }

		static std::string FromUTF32(const char32_t& c);
	};
}