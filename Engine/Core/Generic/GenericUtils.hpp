/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Core
{
    template <typename T, typename U>
    T* Cast(U* pInstance)
    {
        return static_cast<T*>(pInstance);
    }

    template <typename T, typename U>
    T* DynCast(U* pInstance)
    {
        return dynamic_cast<T*>(pInstance);
    }

    template <typename T, typename U>
    T* AddrCast(U* pInstance)
    {
        return reinterpret_cast<T*>(pInstance);
    }

    template <typename T, typename ...Args>
    bool InList(const T& value, Args&&... args) noexcept
    {
        return ((value == args) || ...);
    }

    template <typename T>
    bool InRange(const T& value, const T& begin, const T& end) noexcept
    {
        if constexpr (std::is_convertible<T, MathBaseType>::value)
        {
            return Math::Gte(value, begin) && Math::Lte(value, end);
        }
        else
        {
            return value >= begin && value <= end;
        }
    }

    template <typename U, typename T>
    bool Let(T* pInstance, const std::function<void(U* pIt)>& Callback)
    {
        if (pInstance != nullptr)
        {
            Callback(Cast<U>(pInstance));
            return true;
        }

        return false;
    }

    template <typename U, typename T>
    bool If(const bool& cond, T* pInstance, const std::function<void(U* pIt)>& Callback)
    {
        if (cond && pInstance != nullptr)
        {
            Callback(Cast<U>(pInstance));
            return true;
        }

        return false;
    }

    template <typename U, typename C>
    void Foreach(C container, const std::function<void(U* pIt)>& Callback)
    {
        for (auto const& pInstance : container)
        {
            if (pInstance != nullptr)
            {
                Callback(Cast<U>(pInstance));
            }
        }
    }

    template <typename T>
    inline auto GetVectorSize(const T& vec) noexcept
    {
        return sizeof(typename T::value_type) * vec.size();
    }
}