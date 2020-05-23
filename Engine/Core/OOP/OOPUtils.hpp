/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux
{
    template<typename T>
    class NonCopyable
    {
    public:
        NonCopyable(NonCopyable const&) = delete;
        T& operator=(T const&) = delete;

    protected:
        NonCopyable() = default;
        virtual ~NonCopyable() = default;
    };

    template<typename T>
    class NonMovable
    {
    public:
        NonMovable(NonMovable&&) = delete;
        T& operator=(T&&) = delete;

    protected:
        NonMovable() = default;
        virtual ~NonMovable() = default;
    };

    template<typename T>
    class NonCopyableNorMovable
    {
    public:
        NonCopyableNorMovable(NonCopyableNorMovable const&) = delete;
        T& operator=(T const&) = delete;

        NonCopyableNorMovable(NonCopyableNorMovable&&) = delete;
        T& operator=(T&&) = delete;

    protected:
        NonCopyableNorMovable() = default;
        virtual ~NonCopyableNorMovable() = default;
    };
}