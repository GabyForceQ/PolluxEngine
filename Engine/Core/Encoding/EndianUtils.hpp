/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "../OOP/OOPUtils.hpp"

namespace Pollux::Core
{
    /**************************************************************************************************************************
     * \class Endian Utilities - static
     *************************************************************************************************************************/
    class EndianUtils : public NonCopyableNorMovable<EndianUtils>
    {
    public:
        template <typename T, typename std::enable_if<std::is_unsigned<T>::value>::type* = nullptr>
        static auto DecodeBigEndian(const char* buffer) noexcept
        {
            T res = 0u;

            for (std::uintptr_t i = 0u; i < sizeof(T); i++)
            {
                res |= static_cast<T>(buffer[sizeof(buffer) - i - 1u] << (i * 8u));
            }

            return res;
        }

        template <typename T, typename std::enable_if<std::is_unsigned<T>::value>::type* = nullptr>
        static auto DecodeLittleEndian(const char* buffer) noexcept
        {
            T res = 0u;

            for (std::uintptr_t i = 0u; i < sizeof(T); i++)
            {
                res |= static_cast<T>(buffer[i] << (i * 8u));
            }

            return res;
        }

        template <typename T, typename std::enable_if<std::is_unsigned<T>::value>::type* = nullptr>
        static void EncodeBigEndian(char* buffer, const T value) noexcept
        {
            char* bytes = static_cast<char*>(buffer);

            for (std::uintptr_t i = 0u; i < sizeof(T); i++)
            {
                bytes[i] = static_cast<char>(value >> ((sizeof(T) - i - 1u) * 8u));
            }
        }

        template <typename T, typename std::enable_if<std::is_unsigned<T>::value>::type* = nullptr>
        static void EncodeLittleEndian(char* buffer, const T value) noexcept
        {
            char* bytes = static_cast<char*>(buffer);

            for (std::uintptr_t i = 0u; i < sizeof(T); i++)
            {
                bytes[i] = static_cast<char>(value >> (i * 8u));
            }
        }
    };
}