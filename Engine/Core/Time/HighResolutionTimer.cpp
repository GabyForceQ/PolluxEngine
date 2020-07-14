/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "HighResolutionTimer.hpp"

namespace Pollux::Core
{
#define USE_CLOCK WINDOWS_CLOCK

#ifdef POLLUX_SYSTEM_WINDOWS
    class HighResolutionTimerImpl final
    {
    public:
        HighResolutionTimerImpl()
        {
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&t0);
        }

        void Tick()
        {
            QueryPerformanceCounter(&t1);
            elapsedTime = (t1.QuadPart - t0.QuadPart) * (1000000.0 / frequency.QuadPart);
            t0 = t1;
        }

        double GetElapsedTimeInMicroSeconds()
        {
            return elapsedTime;
        }

    private:
        LARGE_INTEGER t0 = {};
        LARGE_INTEGER t1 = {};
        LARGE_INTEGER frequency = {};
        double elapsedTime = 0.0;
    };
#elif defined(USE_HIGH_RESOLUTION_CLOCK)
    class HighResolutionTimerImpl final
    {
    public:
        HighResolutionTimerImpl()
        {
            t0 = std::chrono::high_resolution_clock::now();
        }

        void Tick()
        {
            t1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::micro> delta = t1 - t0;
            t0 = t1;
            elapsedTime = delta.count();
        }

        double GetElapsedTimeInMicroSeconds()
        {
            return elapsedTime;
        }

    private:
        std::chrono::high_resolution_clock::time_point t0;
        std::chrono::high_resolution_clock::time_point t1;
        double elapsedTime = 0.0;
    };
#elif defined(USE_STEADY_CLOCK)
    class HighResolutionTimerImpl final
    {
    public:
        HighResolutionTimerImpl()
        {
            t0 = std::chrono::steady_clock::now();
        }

        void Tick()
        {
            t1 = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::micro> delta = t1 - t0;
            t0 = t1;
            elapsedTime = delta.count();
        }

        double GetElapsedTimeInMicroSeconds()
        {
            return elapsedTime;
        }

    private:
        std::chrono::steady_clock::time_point t0;
        std::chrono::steady_clock::time_point t1;
        double elapsedTime = 0.0;
    };
#endif

    HighResolutionTimer::HighResolutionTimer()
    {
        m_pHighResolutionTimerImpl = new HighResolutionTimerImpl();
    }

    HighResolutionTimer::~HighResolutionTimer()
    {
        SAFE_DELETE(m_pHighResolutionTimerImpl);
    }

    void HighResolutionTimer::Tick()
    {
        m_pHighResolutionTimerImpl->Tick();
    }

    double HighResolutionTimer::ElapsedSeconds() const
    {
        return m_pHighResolutionTimerImpl->GetElapsedTimeInMicroSeconds() * 0.000001;
    }

    double HighResolutionTimer::ElapsedMilliSeconds() const
    {
        return m_pHighResolutionTimerImpl->GetElapsedTimeInMicroSeconds() * 0.001;
    }

    double HighResolutionTimer::ElapsedMicroSeconds() const
    {
        return m_pHighResolutionTimerImpl->GetElapsedTimeInMicroSeconds();
    }
}