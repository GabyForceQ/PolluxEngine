/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "WorkerThread.hpp"

namespace Pollux::Core
{
    WorkerThread::WorkerThread(std::thread thread) noexcept
        :
        m_Handle{ std::move(thread) }
    {
    }

    WorkerThread::WorkerThread(WorkerThread&& other) noexcept
        :
        m_Handle{ std::move(other.m_Handle) }
    {
    }

    WorkerThread& WorkerThread::operator=(WorkerThread&& other) noexcept
    {
        if (IsJoinable())
        {
            Join();
        }

        m_Handle = std::move(other.m_Handle);
        return *this;
    }

    WorkerThread& WorkerThread::operator=(std::thread other) noexcept
    {
        if (IsJoinable())
        {
            Join();
        }

        m_Handle = std::move(other);
        return *this;
    }

    WorkerThread::~WorkerThread() noexcept
    {
        if (IsJoinable())
        {
            Join();
        }
    }

    void WorkerThread::Swap(WorkerThread& other) noexcept
    {
        m_Handle.swap(other.m_Handle);
    }

    void WorkerThread::Join()
    {
        m_Handle.join();
    }

    void WorkerThread::Detach()
    {
        m_Handle.detach();
    }

    void WorkerThread::SetPriority(const float& priority)
    {
        static constexpr int32_t priorities[] =
        {
            THREAD_PRIORITY_IDLE,
            THREAD_PRIORITY_LOWEST,
            THREAD_PRIORITY_BELOW_NORMAL,
            THREAD_PRIORITY_NORMAL,
            THREAD_PRIORITY_ABOVE_NORMAL,
            THREAD_PRIORITY_HIGHEST,
            THREAD_PRIORITY_TIME_CRITICAL
        };

        if (!SetThreadPriority(m_Handle.native_handle(), priorities[static_cast<size_t>((priority + 1.f) * 3.f)]))
        {
            throw std::system_error(GetLastError(), std::system_category(), "Failed to set thread priority.");
        }
    }

    bool WorkerThread::IsJoinable() const noexcept
    {
        return m_Handle.joinable();
    }

    std::thread::id WorkerThread::GetID() const noexcept
    {
        return m_Handle.get_id();
    }

    std::thread& WorkerThread::GetHandle() noexcept
    {
        return m_Handle;
    }

    std::thread::native_handle_type WorkerThread::GetNativeHandle() noexcept
    {
        return m_Handle.native_handle();
    }

    const std::thread& WorkerThread::GetHandle() const noexcept
    {
        return m_Handle;
    }
}