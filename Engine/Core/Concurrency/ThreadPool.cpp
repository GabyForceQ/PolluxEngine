/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "Engine/enginepch.hpp"

#include "ThreadPool.hpp"

namespace Pollux::Core
{
    void ThreadPool::SetThreadCount(const size_t& count)
    {
        m_ThreadCount = count;
        m_pThreads.clear();

        for (size_t i = 0_sz; i < count; i++)
        {
            m_pThreads.push_back(std::make_unique<Thread>());
        }
    }

    const size_t& ThreadPool::GetThreadCount() const noexcept
    {
        return m_ThreadCount;
    }

    void ThreadPool::Wait()
    {
        for (const auto& pThread : m_pThreads)
        {
            pThread->Wait();
        }
    }
}